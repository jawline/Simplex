#ifndef _ROW_DEF_H_
#define _ROW_DEF_H_

typedef struct {
  float* data;
} row;

void initialiseRow(row* instance, unsigned int numColumns);
void expandRow(row* instance, unsigned int numNewColumns);
void freeRow(row* instance);

#endif //_ROW_DEF_H_
