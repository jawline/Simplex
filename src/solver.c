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

	return cPivot;
}

int findPivotRow(table* instance, int column) {
	int resultsRow = instance->numColumns - 1;
	int cPivot = 0;
	float cPivotR;
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (getTableField(instance, cPivot, column))
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

	int pivotC = findPivotColumn(instance);
	int pivotR = findPivotRow(instance, pivotC);
	printf("Pivot Column %i\n", pivot);

	free(rowBasicData);
}