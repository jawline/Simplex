#ifndef _COLUMN_DEF_H_
#define _COLUMN_DEF_H_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct {
  char* name;
} column;

void initialiseColumn(column* column, char const* name, size_t nameLength);
void freeColumn(column* column);

#endif //_COLUMN_DEF_H_
