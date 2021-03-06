#include "tableau.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialiseTable(table* instance) {
	instance->columns = 0;
	instance->numColumns = 0;
	instance->rowData = 0;
	instance->numRows = 1;
}

void freeTable(table* instance) {
	if (instance->columns) {
		for (unsigned int i = 0; i < instance->numColumns; i++) {
			freeColumn(&instance->columns[i]);
		}
		free(instance->columns);
		instance->columns = 0;
	}
	if (instance->rowData) {
		free(instance->rowData);
		instance->rowData = 0;
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

	//Allocate memory and copy existing columns
	column* newColumns = malloc(sizeof(column) * (instance->numColumns + 1));
	memcpy(newColumns, instance->columns, sizeof(column) * instance->numColumns);
	
	//Free existing data and set new data
	if (instance->columns) {
		free(instance->columns);
	}
	instance->columns = newColumns;
	
	//Initialise new column
	initialiseColumn(&instance->columns[instance->numColumns], name, nameLength);
	
	//Expand existing row data
	expandRows(instance, instance->numColumns, instance->numColumns+1);
	return instance->numColumns++;
}

void addTableRow(table* instance) {
	
	//Allocate memory and copy over existing rows
	double* newRowData = malloc(sizeof(double) * (instance->numRows + 1) * instance->numColumns);
	memcpy(newRowData, instance->rowData, sizeof(double) * instance->numRows * instance->numColumns);
	
	//Set new rows to 0
	memset(newRowData + (instance->numRows * instance->numColumns), 0, sizeof(double) * instance->numColumns);

	//Free old data and set new row data
	if (instance->rowData) {
		free(instance->rowData);
	}
	instance->rowData = newRowData;
	instance->numRows++;
}

void expandRows(table* instance, int oldNumColumns, int newNumColumns) {
	
	//Allocate new data
	double* newRowData = malloc(sizeof(double) * instance->numRows * newNumColumns);
	double* oldRowData = instance->rowData;
	memset(newRowData, 0, newNumColumns * instance->numRows * sizeof(double));
	
	//Copy the existing rows
	for (unsigned int column = 0; column < oldNumColumns; column++) {
		for (unsigned int row = 0; row < instance->numRows; row++) {
			newRowData[(row * newNumColumns) + column] = oldRowData[(row * oldNumColumns) + column];
		}
	}
	
	//Free old data and set new data
	if (instance->rowData) {
		free(instance->rowData);
	}
	instance->rowData = newRowData;
}

unsigned int getCurrentRow(table* instance) {
	if (!instance->rowData) {
		return 0;
	}
	return instance->numRows - 1;
}

double* getRowData(table* instance, unsigned int rowNum) {
	return instance->rowData + (instance->numColumns * rowNum);
}

double getTableField(table* instance, unsigned int row, unsigned int column) {
	return *(getRowData(instance, row) + column);
}

void setTableField(table* instance, unsigned int row, unsigned int column, double val) {
	*(getRowData(instance, row) + column) = val;
}

double getTableFieldWithColumnNameAndLength(table* instance, unsigned int row, char const* columnName, int length) {
	int col;
	if ((col = getTableColumnIdWithLength(instance, columnName, length)) == -1) {
		printf("Column %s does not exist\n", columnName);
		return 0;
	}
	return getTableField(instance, row, col);	
}

void setTableFieldWithColumnNameAndLength(table* instance, unsigned int row, char const* columnName, int length, double val) {
	int col;
	if ((col = getTableColumnIdWithLength(instance, columnName, length)) == -1) {
		printf("Column %s does not exist\n", columnName);
		return;
	}
	setTableField(instance, row, col, val);
}

double getTableFieldWithColumnName(table* instance, unsigned int row, char const* columnName) {
	return getTableFieldWithColumnNameAndLength(instance, row, columnName, strlen(columnName));
}

void setTableFieldWithColumnName(table* instance, unsigned int row, char const* columnName, double val) {
	setTableFieldWithColumnNameAndLength(instance, row, columnName, strlen(columnName), val);
}

void swapTableColumn(table* instance, unsigned int a, unsigned int b) {
	double temp;
	for (unsigned int i = 0; i < instance->numRows; i++) {
		temp = getTableField(instance, i, a);
		setTableField(instance, i, a, getTableField(instance, i, b));
		setTableField(instance, i, b, temp);
	}
	column tempCol = instance->columns[a];
	instance->columns[a] = instance->columns[b];
	instance->columns[b] = tempCol;
}

void printTable(table* instance) {
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		printf("| %s |", instance->columns[i].name);
	}
	printf("\n");
	for (unsigned int row = 0; row < instance->numRows; row++) {
		for (unsigned int column = 0; column < instance->numColumns; column++) {
			printf("| %f |", instance->rowData[row * instance->numColumns + column]);
		}
		printf("\n");
	}
}
