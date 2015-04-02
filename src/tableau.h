#ifndef _SIMPLEX_TABLAEU_DEF_H_
#define _SIMPLEX_TABLAEU_DEF_H_
#include "column.h"

typedef struct {
  column* columns;
  float* rowData;
  int numColumns;
  int numRows;
} table;

/**
 * Initialise all the table values
 */
void initialiseTable(table* instance);

/**
 * Free any memory associated with the table instance
 */
void freeTable(table* instance);

/**
 * Get the index of the column in the table
 */
int getTableColumnId(table* instance, char const* name);

/**
 * Get a columns information from the table
 */
column* getTableColumn(table* instance, char const* name);

/**
 * Add a new column to the table
 */
int addTableColumn(table* instance, char const* name, size_t nameLength);
int getTableColumnIdWithLength(table* instance, char const* name, size_t nameLength);

/**
 * Add a new row to the table
 */
void addTableRow(table* instance);

/**
 * Expand all the rows after a column is added to the table
 */
void expandRows(table* instance, int oldNumColumns, int newNumColumns);

/**
 * Return a pointer to the last row added to the table
 */
float* getCurrentRow();

/**
 * Print debug info about the table
 */
void printTable(table* instance);

#endif //_SIMPLEX_TABLAEU_DEF_H_
