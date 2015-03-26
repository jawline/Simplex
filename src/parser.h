#ifndef _SIMPLEX_PARSER_DEF_H_
#define _SIMPLEX_PARSER_DEF_H_

/**
 * ID = \[a-zA-Z]+[0-9]*\
 * NUM = \[0-9]+(.[0-9]+)?\
 * Grammar:
 * MinMax: max Expression NEWLINE ['s.t.' Constraints]
 * Constraints: Constraint [NEWLINE Constraints]
 * Constraint: Expression '=' Expression
 * Expression: (ID | NUM | NUM ID) [('+' | '-') Expression]
 */
 
 typedef enum { MAX = 0, ID, NUM, NEWLINE, ST, EQ, PLUS, MINUS } TOKEN;
 
 void parserInit();
 void parseString(char const* input);
 void parserFree();

#endif //_SIMPLEX_PARSER_DEF_H_
