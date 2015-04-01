#include "tableau.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialiseTable(table* instance) {
	instance->columns = 0;
	instance->numColumns = 0;
	instance->rowData = 0;
	instance->numRows = 0;
}

void freeTable(table* instance) {
	if (instance->columns) {
		for (unsigned int i = 0; i < instance->numColumns; i++) {
			freeColumn(&instance->columns[i]);
		}
		free(instance->columns);
		instance->columns = 0;
	}
	if (instance->rows) {
		free(instance->rows);
		instance->rows = 0;
	}
}

int getTableColumnId(table* instance, char const* name) {
	for (int i = 0; i < instance->numColumns; i++) {
		if (strcmp(instance->columns[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

int getTableColumnIdWithLength(table* instance, char const* name, size_t nameLength) {
	for (int i = 0; i < instance->numColumns; i++) {
		if (strncmp(instance->columns[i].name, name, nameLength) == 0) {
			return i;
		}
	}
	return -1;
}

column* getTableColumn(table* instance, char const* name) {
	int temp;
	if ((temp = getTableColumnId(instance, name)) != -1) {
		return &instance->columns[temp];
	}
	return 0;
}

int addTableColumn(table* instance, char const* name, size_t nameLength) {
	if (getTableColumnIdWithLength(instance, name, nameLength) != -1) {
		return getTableColumnIdWithLength(instance, name, nameLength);
	}

	column* newColumns = malloc(sizeof(column) * (instance->numColumns + 1));
	memcpy(newColumns, instance->columns, sizeof(column) * instance->numColumns);
	instance->columns = newColumns;
	initialiseColumn(&instance->columns[instance->numColumns], name, nameLength);
	return instance->numColumns++;
}

void addRow(table* instance) {
	
	//Allocate memory and copy over existing rows
	float* newRowData = malloc(sizeof(float) * (instance->numRows + 1) * instance->numColumns);
	memcpy(newRowData, instance->rowData, sizeof(float) * instance->numRows * instance->numColumns);
	
	//Set new rows to 0
	memset(newRowData + (instance->numRows * instance->numColumns), 0, sizeof(float) * instance->numColumns);

	//Free old data and set new row data
	if (instance->rowData) {
		free(instance->rowData);
	}
	instance->rowData = newRowData;
}

void expandRows(table* instance, int oldNumColumns, int newNumColumns) {
	
	//Allocate new data
	float* newRowData = malloc(sizeof(float) * instance->numRows * newNumColumns);
	float* oldRowData = instance->rowData;
	memset(newRowData, 0, numNewColumns * instance->numRows * sizeof(float));
	
	//Copy the existing rows
	for (unsigned int column = 0; column < oldNumColumns; column++) {
		for (unsigned int row = 0; row < instance->numRows; row++) {
			newRowData[(row * oldNumColumns) + column] = oldRowData[(row * oldNumColumns) + column];
		}
	}
	
	//Free old data and set new data
	if (instance->rowData) {
		free(instance->rowData);
	}
	instance->rowData = newRowData;
}

void printTable(table* instance) {
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		printf("| %s |", instance->columns[i].name);
	}
	printf("\n");
}
