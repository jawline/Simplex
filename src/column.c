#include "column.h"

void initialiseColumn(column* column, char const* name, size_t nameLength) {
	column->name = malloc(nameLength + 1);
	memcpy(column->name, name, nameLength);
	column->name[nameLength] = '\0';
}

void freeColumn(column* column) {
	free(column->name);
}