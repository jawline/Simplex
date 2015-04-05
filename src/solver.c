#include "solver.h"

bool isBasic(table* instance, int col) {
	unsigned int count = 0;
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (getTableField(instance, i, col) != 0) {
			count++;
		}
	}
	return count > 0;
}

int findBasic(table* instance, int row) {
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		if (isBasic(instance, i)) {
			return i;
		}
	}
	return -1;
}

void solveTable(table* instance) {
	
	//Find the initial basic variables (Only occur in one col)
	int* rowBasicData = malloc(sizeof(int) * instance->numRows);
	
	for (unsigned int i = 0; i < instance->numRows; i++) {
		rowBasicData[i] = findBasic(instance, i);
	}

	free(rowBasicData);
}