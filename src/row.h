#ifndef _ROW_DEF_H_
#define _ROW_DEF_H_

typedef struct {
  float* data;
} row;

/**
 * Initialise a row
 */
void initialiseRow(row* instance, unsigned int numColumns);

/**
 * Expands the row size from numOldColumns to numNewColumns
 */
void expandRow(row* instance, unsigned int numOldColumns, unsigned int numNewColumns);

/**
 * Free any memory associated with a row
 */
void freeRow(row* instance);

#endif //_ROW_DEF_H_
