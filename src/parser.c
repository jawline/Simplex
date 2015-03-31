#include "parser.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <regexpm/match.h>
#include <regexpm/parser.h>

regex idRegex;
regex numRegex;

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
  size_t regexLen;
  input = skipWhite(input);

  if (strncmp(input, "max", 3) == 0) {
    *token = MAX;
    return input + 3;
  } else if (strncmp(input, "s.t.", 4) == 0) {
    *token = ST;
    return input + 4;
  } else if (*input == ',') {
    *token = COMMA;
    return input + 1;
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
    *token = PEOF;
    return input;
  } else if ((regexLen = nfaMatches(idRegex.start, input)) > 0) {
    *token = ID;
    return input + regexLen;
  } else if ((regexLen = nfaMatches(numRegex.start, input)) > 0) {
    *token = NUM;
    return input + regexLen;
  }
  
  printf("Could not parse valid token from \"%s\"\n", input);
  
  return 0;
}

void parserInit() {
  regexParse(&idRegex, "[a-zA-Z][a-zA-Z0-9]*");
  regexParse(&numRegex, "[0-9]+(.[0-9]+)?");
}

char const* parseExpression(char const* input) {
  TOKEN token;
  
  char const* tempInput;
  input = nextToken(&token, input);

  if (!input) {
    return 0;
  }
  
  if (token == ID) {
    printf("Handle ID\n");
  } else if (token == NUM) {
    if ((tempInput = nextToken(&token, input)) && token == ID) {
      printf("NUM * ID\n");
      input = tempInput;
    } else {
      printf("NUM\n");
    }
  } else {
    printf("Expected ID, NUM or NUM ID near \"%s\"\n", input);
    return 0;
  }
  
  printf("Parsed expression\n");
  
  if ((tempInput = nextToken(&token, input)) && (token == PLUS || token == MINUS)) {
    return parseExpression(tempInput);
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
  TOKEN token;
  input = parseConstraint(input);
  
  if (!input) {
    return 0;
  }
  
  if (nextToken(&token, input) && token == COMMA) {
    return parseConstraints(input);
  } else {
    printf("Parsed Constraints");
    return input;
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
  
  input = nextToken(&token, input);
  
  if (!input) {
    return false;
  }
  
  if (token != ID) {
    printf("Expected ID near \"%s\"", input);
    return false;
  }
  
  printf("Maximizing ID\n");
  
  input = nextToken(&token, input);
  
  if (!input) {
    return false;
  }
  
  if (token != EQ) {
    printf("Expected EQ near \"%s\"", input);
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
  
  if (token == PEOF) {
    return true;
  } else if (token != ST) {
    printf("Expected 's.t.' to be the next token near \"%s\"\n", input);
    return false;
  }
  
  input = parseConstraints(input);
  
  if (!input) {
    return false;
  }
  
  if (token != PEOF) {
    printf("Unexpected symbol near \"%s\"\n", input);
    return false;
  } else {
    return true;
  }
}

void parserFree() {
  regexFree(&idRegex);
  regexFree(&numRegex);
}
