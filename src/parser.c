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
  } else if (*input == '\0') {
    *token = EOF;
    return input;
  }
  
  printf("Could not parse valid token from %s\n", input);
  
  return 0;
}

void parserInit() {}

char const* parseExpression(char const* input) {
  TOKEN token;
  
  input = nextToken(&token, input);
  if (!input) {
    return 0;
  }
  
  if (token == ID) {
    printf("Handle ID\n");
  } else if (token == NUM) {
    if (nextToken(&token, input) && token == ID) {
      printf("NUM * ID\n");
    } else {
      printf("NUM\n");
    }
  } else {
    printf("Expected ID, NUM or NUM ID near %s\n", input);
    return 0;
  }
  
  printf("Parsed expression\n");
  
  if (nextToken(&token, input) && (token == PLUS || token == MINUS)) {
    return parseExpression(input);
  } else {
    return input;
  }
}

char const* parseConstraint(char const* input) {
  TOKEN token;
  
  input = parseExpression(input);
  if (!input) {
    return 0;
  }
  
  input = nextToken(&token, input);
  
  if (!input) {
    return 0;
  }
  
  if (token != EQ) {
    printf("Expected equals near %s\n", input);
    return 0;
  }
  
  input = nextToken(&token, input);
  
  if (!input) {
    return 0;
  }
  
  if (token != NUM) {
    printf("Expected NUM near %s\n", input);
    return 0;
  }
  
  printf("Parsed constraint\n");
  return input;
}

char const* parseConstraints(char const* input) {
  
  input = parseConstraint(input);
  
  if (!input) {
    return 0;
  }
  
  if (nextToken(&token, input) && nextToken == EOF) {
    return input;
  } else {
    return parseConstraints(char const* input);
  }
}

bool parseString(char const* input) {
  TOKEN token;
  input = nextToken(&token, input);
  
  if (!input) {
    return false;
  }

  if (token != MAX) {
    printf("Expected max to be the next token near %s\n", input);
    return false;
  }
  
  input = parseExpression(input);
  
  if (!input) {
    return false;
  }
  
  input = nextToken(&token, input);
  
  if (!input) {
    return false;
  }
  
  if (token == EOF) {
    return true;
  } else if (token != ST) {
    printf("Expected 's.t.' to be the next token near %s\n", input);
    return false;
  }
  
  return parseConstraints(input) != 0;
}

void parserFree() {}
