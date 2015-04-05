#ifndef _TABLEAU_SOLVER_DEF_H_
#define _TABLEAU_SOLVER_DEF_H_
#include <stdbool.h>
#include "tableau.h"

bool isBasic(table* instance, int col);

/**
 * Solve the simplex tableau
 * NOTE: It is assumed that the last column in the table is the results column
 */
void solveTable(table* instance);

#endif //_TABLEAU_SOLVER_DEF_H_