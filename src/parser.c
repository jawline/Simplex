#include "parser.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * Skip whitespace until the end of the input or the next character is found
 */
char const* skipWhite(char const* input) {
  for (; *input && isspace(*input); input++) {}
  return input;
}

/**
 * Get the next token from the input string
 */
char const* nextToken(TOKEN* token, char const* input) {
  input = skipWhite(input);

  if (strncmp(input, "max", 3) == 0) {
    *token = MAX;
    return input + 3;
  } else if (strncmp(input, "s.t.", 4) == 0) {
    *token = ST;
    return input + 4;
  } else if (*input == '=') {
    *token = EQ;
    return input + 1;
  } else if (*input == '+') {
    *token = PLUS;
    return input + 1;
  } else if (*input == '-') {
    *token = MINUS;
    return input + 1;
  }
  
  printf("Could not parse valid token from %s\n", input);
  
  return 0;
}

void parserInit() {}

char const* parseExpression(char const* input) {
  return input;
}

bool parseString(char const* input) {
  TOKEN nextToken;
  input = nextToken(&nextToken, input);
  
  if (!input) {
    return false;
  }

  if (nextToken != MAX) {
    printf("Expected max to be the next token near %s\n", input);
    return false;
  }
  
  input = parseExpression(input);
  
  if (!input) {
    return false;
  }
  
  input = nextToken(&nextToken, input);
  
  if (!input) {
    return false;
  }
  
  if (nextToken != ST) {
    printf("Expected 's.t.' to be the next token near %s\n", input);
    return false;
  }
}

void parserFree() {}
