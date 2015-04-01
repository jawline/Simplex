#include "row.h"
#include <stdlib.h>
#include <string.h>

void initialiseRow(row* instance, unsigned int numColumns) {
  instance->data = 0;
  expandRow(instance, 0, numColumns);
}

void expandRow(row* instance, unsigned int numOldColumns, unsigned int numNewColumns) {
  float* newData = malloc(sizeof(float) * numNewColumns);
  memcpy(newData, instance->data, sizeof(float) * numOldColumns);
  memset(newData + numOldColumns, 0, sizeof(float) * (numNewColumns - numOldColumns));
}

void freeRow(row* instance) {
  if (instance->data) {
    free(instance->data);
    instance->data = 0;
  }
}
