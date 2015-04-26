#include "solver.h"
#include <stdio.h>

bool isBasic(table* instance, int col) {
	unsigned int count = 0;
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (getTableField(instance, i, col) != 0) {
			count++;
		}
	}
	return count == 1;
}

//TODO: Could be more efficient. The row->col->row search could be turned into just a row->col search
int findBasic(table* instance, int row) {

	//-1 excludes the result row
	for (unsigned int i = 0; i < instance->numColumns - 1; i++) {
		if (isBasic(instance, i) && getTableField(instance, row, i) != 0) {
			return i;
		}
	}
	return -1;
}

/**
 * Return the ID of the pivot column or -1 if there is not pivot column
 */
int findPivotColumn(table* instance) {
	int cPivot = 1;
	double cPivotValue = getTableField(instance, 0, 1);

	//Slight optimization, as the first row will never change and will never be the pivot it can be excluded
	for (unsigned int i = 1; i < instance->numColumns - 1; i++) {
		if (getTableField(instance, 0, i) != 0 && (getTableField(instance, 0, i) < cPivotValue || cPivotValue == 0)) {
			cPivot = i;
			cPivotValue = getTableField(instance, 0, i);
		}
	}

	//If the columns objective value is >= 0 then it cannot be a pivot column
	return getTableField(instance, 0, cPivot) != 0 ? cPivot : -1;
}

double findRatio(table* instance, int row, int column, int resCol) {
	return getTableField(instance, row, resCol) / getTableField(instance, row, column);
}

int findPivotRow(table* instance, int column) {

	if (instance->numRows < 2) {
		printf("no pivot possible\n");
		return -1;
	}

	int resultsColumn = instance->numColumns - 1;
	
	int cPivot = 1;
	double cPivotR = findRatio(instance, 1, column, resultsColumn);
	
	//Find the row to be used as the pivot, excluding the objective function
	for (unsigned int i = 1; i < instance->numRows; i++) {
		if (findRatio(instance, i, column, resultsColumn) < cPivotR) {
			cPivot = i;
			cPivotR = findRatio(instance, i, column, resultsColumn);
		}
	}

	return cPivot;
}

void makeRowUnit(table* instance, int row, int col) {
	double ratio = 1.0 / getTableField(instance, row, col);
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		setTableField(instance, row, i, ratio * getTableField(instance, row, i));
	}
}

void subtractRow(table* instance, int rowToSub, int rowFrom, double ratio) {
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		setTableField(instance, rowToSub, i, getTableField(instance, rowToSub, i) - (getTableField(instance, rowFrom, i) / ratio));
	}
}

void makeOtherRowsUnit(table* instance, int baseRow, int col) {
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (i != baseRow && getTableField(instance, i, col) != 0) {
			double ratioOfBaseRow = 1/getTableField(instance, i, col);
			subtractRow(instance, i, baseRow, ratioOfBaseRow);
		}
	}
}

void solveTable(table* instance, simplex_result* results) {
	
	//Find the initial basic variables (Only occur in one col)
	int* rowBasicData = malloc(sizeof(int) * instance->numRows);
	double* rowBasicSolution = malloc(sizeof(double) * instance->numRows);
	memset(rowBasicData, 0, sizeof(int) * instance->numRows);
	
	printf("---------\n");

	//First row is the objective function, should have no basic variables
	for (unsigned int i = 1; i < instance->numRows; i++) {
		rowBasicData[i] = findBasic(instance, i);
		if (rowBasicData[i] == -1) {
			printf("Failed to find basic variable for row %i\n", i);
			rowBasicSolution = 0;
		} else {
			rowBasicSolution[i] = getTableField(instance, i, rowBasicData[i]) / getTableField(instance, i, instance->numColumns - 1);
			printf("Row %i: Col %i is basic (Solution: %f/%f -> %f)\n",
				i,
				rowBasicData[i],
				getTableField(instance, i, rowBasicData[i]),
				getTableField(instance, i, instance->numColumns - 1),
				rowBasicSolution[i]);
		}
	}
	
	printf("---------\n");

	int pivotC;
	int i = 0;
	while ((pivotC = findPivotColumn(instance)) != -1 && i < 4) {
		int pivotR = findPivotRow(instance, pivotC);
		double ratio = findRatio(instance, pivotR, pivotC, instance->numColumns-1);
		printf("Pivot Column %i\n", pivotC);
		printf("Pivot Row: %i\n", pivotR);
		printf("Pivot Ratio: %f\n", ratio);
		makeRowUnit(instance, pivotR, pivotC);
		makeOtherRowsUnit(instance, pivotR, pivotC);
		printTable(instance);
		rowBasicData[pivotR] = pivotC;
		i++;
	}


	printf("---------\n");
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (rowBasicData[i] != -1) {
			printf("%s: %f\n",
				instance->columns[i].name, 
				getTableField(instance, i, instance->numColumns - 1));
		} else {
			printf("Row %i unmapped\n", i);
		}
	}
	printf("---------\n");

	free(rowBasicData);
	results->value = getTableField(instance, 0, instance->numColumns - 1);
}
