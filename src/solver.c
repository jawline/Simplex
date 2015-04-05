#include "solver.h"

bool isBasic(table* instance, int col) {
	unsigned int count = 0;
	for (unsigned int i = 0; i < instance->numRows; i++) {
		if (getTableField(instance, i, col) != 0) {
			count++;
		}
	}
	return count > 0;
}