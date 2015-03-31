#ifndef _SIMPLEX_TABLAEU_DEF_H_
#define _SIMPLEX_TABLAEU_DEF_H_
#include "column.h"
#include "row.h"

typedef struct {
  column* columns;
  int numColumns;
  
  row** rows;
  int numRows;
} table;

void initialiseTable(table* instance);
void freeTable(table* instance);

int getTableColumnId(table* instance, char const* name);
int getTableColumnIdWithLength(table* instance, char const* name, size_t nameLength);
column* getTableColumn(table* instance, char const* name);
int addTableColumn(table* instance, char const* name, size_t nameLength);

void printTable(table* instance);

#endif //_SIMPLEX_TABLAEU_DEF_H_
