#include "tableau.h"
#include <stdlib.h>
#include <string.h>

void initialiseTable(table* instance) {
	instance->columns = 0;
	instance->numColumns = 0;

	instance->rows = 0;
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

column* getTableColumn(table* instance, char const* name) {
	int temp;
	if ((temp = getTableColumnId(instance, name)) != -1) {
		return &instance->columns[temp];
	}
	return 0;
}

int addTableColumn(table* instance, char const* name, size_t nameLength) {
	if (getTableColumnId(instance, name) != -1) {
		return getTableColumnId(instance, name);
	}

	column* newColumns = malloc(sizeof(column) * (instance->numColumns + 1));
	memcpy(newColumns, instance->columns, sizeof(column) * instance->numColumns);
	initialiseColumn(&instance->columns[instance->numColumns], name, nameLength);
	return instance->numColumns++;
}