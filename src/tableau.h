#ifndef _SIMPLEX_TABLAEU_DEF_H_
#define _SIMPLEX_TABLAEU_DEF_H_
#include "column.h"
#include "row.h"

typedef struct {
  column* columns;
  unsigned int numColumns;
  
  row** rows;
  unsigned int numRows;
} table;

void initialiseTable(table* instance);
void freeTable(table* instance);

int getTableColumnId(table* instance);
column* getTableColumn(table* instance);
int addTableColumn(char const* name, unsigned int nameLength);

#endif //_SIMPLEX_TABLAEU_DEF_H_
