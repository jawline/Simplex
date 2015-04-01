#ifndef _SIMPLEX_TABLAEU_DEF_H_
#define _SIMPLEX_TABLAEU_DEF_H_
#include "column.h"

typedef struct {
  column* columns;
  float* rowData;

  int numColumns;
  int numRows;
} table;

void initialiseTable(table* instance);
void freeTable(table* instance);

int getTableColumnId(table* instance, char const* name);
int getTableColumnIdWithLength(table* instance, char const* name, size_t nameLength);
column* getTableColumn(table* instance, char const* name);
int addTableColumn(table* instance, char const* name, size_t nameLength);

void addTableRow(table* instance);
void expandRows(table* instance, int oldNumColumns, int newNumColumns);

void printTable(table* instance);

#endif //_SIMPLEX_TABLAEU_DEF_H_
