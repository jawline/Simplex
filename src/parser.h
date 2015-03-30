#ifndef _SIMPLEX_PARSER_DEF_H_
#define _SIMPLEX_PARSER_DEF_H_

/**
 * ID = \[a-zA-Z][a-zA-Z0-9]*\
 * NUM = \[0-9]+(.[0-9]+)?\
 * Grammar:
 * MinMax: max Expression ['s.t.' Constraints]
 * Constraints: Constraint [Constraints]
 * Constraint: Expression '=' Expression
 * Expression: (ID | NUM | NUM ID) [('+' | '-') Expression]
 */
 
typedef enum {
 MAX = 0,
 ID,
 NUM,
 ST,
 EQ,
 PLUS,
 MINUS
} TOKEN;
 
 void parserInit();
 void parseString(char const* input);
 void parserFree();

#endif //_SIMPLEX_PARSER_DEF_H_
