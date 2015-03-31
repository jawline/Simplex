#ifndef _SIMPLEX_TABLAEU_DEF_H_
#define _SIMPLEX_TABLAEU_DEF_H_
#include "column.h"
#include "row.h"

typedef struct {
  column** columns;
  unsigned int numColumns;
  
  row** rows;
  unsigned int numRows;
} table;

#endif //_SIMPLEX_TABLAEU_DEF_H_
