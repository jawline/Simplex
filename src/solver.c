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

int findPivotColumn(table* instance) {
	int cPivot = 0;

	for (unsigned int i = 1; i < instance->numColumns - 1; i++) {
		if (getTableField(instance, 0, i) < getTableField(instance, 0, cPivot)) {
			cPivot = i;
		}
	}

	return getTableField(instance, 0, cPivot) < 0 ? cPivot : -1;
}

float findRatio(table* instance, int row, int column, int resCol) {
	return getTableField(instance, row, resCol) / getTableField(instance, row, column);
}

int findPivotRow(table* instance, int column) {

	if (instance->numRows < 2) {
		printf("no pivot possible\n");
		return -1;
	}

	int resultsColumn = instance->numColumns - 1;
	
	int cPivot = 1;
	float cPivotR = findRatio(instance, 1, column, resultsColumn);
	
	//Row 0 is objective function
	for (unsigned int i = 1; i < instance->numRows; i++) {
		if (findRatio(instance, i, column, resultsColumn) < cPivotR) {
			cPivot = i;
			cPivotR = findRatio(instance, i, column, resultsColumn);
		}
	}

	return cPivot;
}

void makeRowUnit(table* instance, int row, int col) {
	float ratio = 1/getTableField(instance, row, col);
	printf("Ratio %f\n", ratio);
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		setTableField(instance, row, i, ratio * getTableField(instance, row, i));
	}
}

void subtractRow(table* instance, int rowToSub, int rowFrom, float ratio) {
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		setTableField(instance, rowToSub, i, getTableField(instance, rowToSub, i) - (getTableField(instance, rowFrom, i) * ratio));
	}
}

void makeOtherRowsUnit(table* instance, int baseRow, int col) {
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (i != baseRow && getTableField(instance, i, col) != 0) {
			float ratioOfBaseRow = 1/getTableField(instance, i, col);
			printf("Row %i needs to be made unit\n", i);
			printf("Ratio (%f)\n", ratioOfBaseRow);
			subtractRow(instance, i, baseRow, ratioOfBaseRow);
		}
	}
}

void solveTable(table* instance) {
	//NOTE: It is assumed that the last column in the table is the results column
	
	//Find the initial basic variables (Only occur in one col)
	int* rowBasicData = malloc(sizeof(int) * instance->numRows);
	float* rowBasicSolution = malloc(sizeof(float) * instance->numRows);
	
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
	while ((pivotC = findPivotColumn(instance)) != -1) {
		int pivotR = findPivotRow(instance, pivotC);
		float ratio = findRatio(instance, pivotR, pivotC, instance->numColumns-1);

		printf("Pivot Column %i\n", pivotC);
		printf("Pivot Row: %i\n", pivotR);
		printf("Pivot Ratio: %f\n", ratio);

		printTable(instance);
		printf("Make unit\n");
		makeRowUnit(instance, pivotR, pivotC);
		makeOtherRowsUnit(instance, pivotR, pivotC);
		printTable(instance);
	}

	free(rowBasicData);
}