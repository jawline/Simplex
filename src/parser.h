#ifndef _SIMPLEX_PARSER_DEF_H_
#define _SIMPLEX_PARSER_DEF_H_
#include <stdbool.h>

/**
 * ID = \[a-zA-Z][a-zA-Z0-9]*\
 * NUM = \[0-9]+(.[0-9]+)?\
 * Grammar:
 * MinMax: max Expression ['s.t.' Constraints]
 * Constraints: Constraint [',' Constraints]
 * Constraint: Expression '=' NUM
 * Expression: (ID | NUM | NUM ID) [('+' | '-') Expression]
 */
 
typedef enum {
 MAX = 0,
 ID,
 NUM,
 ST,
 EQ,
 PLUS,
 MINUS,
 COMMA,
 PEOF
} TOKEN;
 
 void parserInit();
 bool parseString(char const* input);
 void parserFree();

#endif //_SIMPLEX_PARSER_DEF_H_
