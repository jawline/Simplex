#ifndef _COLUMN_DEF_H_
#define _COLUMN_DEF_H_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct {
  char* name;
} column;

/**
 * Initialise a column
 */
void initialiseColumn(column* column, char const* name, size_t nameLength);

/**
 * Free any memory associated with a column
 */
void freeColumn(column* column);

#endif //_COLUMN_DEF_H_
