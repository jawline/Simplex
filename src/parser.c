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
char const* nextToken(TOKEN* token, char const* input, char const** tokenStart, size_t* tokenSize) {
  size_t regexLen;
  input = skipWhite(input);
  *tokenStart = input;

  if (strncmp(input, "max", 3) == 0) {
    *token = MAX;
    *tokenSize = 3;
    return input + 3;
  } else if (strncmp(input, "s.t.", 4) == 0) {
    *token = ST;
    *tokenSize = 4;
    return input + 4;
  } else if (*input == ',') {
    *token = COMMA;
    *tokenSize = 1;
    return input + 1;
  } else if (*input == '=') {
    *token = EQ;
    *tokenSize = 1;
    return input + 1;
  } else if (*input == '+') {
    *token = PLUS;
    *tokenSize = 1;
    return input + 1;
  } else if (*input == '-') {
    *token = MINUS;
    *tokenSize = 1;
    return input + 1;
  } else if (*input == '\0') {
    *token = PEOF;
    *tokenSize = 0;
    return input;
  } else if ((regexLen = nfaMatches(idRegex.start, input)) > 0) {
    *token = ID;
    *tokenSize = regexLen;
    return input + regexLen;
  } else if ((regexLen = nfaMatches(numRegex.start, input)) > 0) {
    *token = NUM;
    *tokenSize = regexLen;
    return input + regexLen;
  }
  
  printf("Could not parse valid token from \"%s\"\n", input);
  return 0;
}

void parserInit() {
  regexParse(&idRegex, "[a-zA-Z][a-zA-Z0-9]*");
  regexParse(&numRegex, "[0-9]+(.[0-9]+)?");
}

char const* parseExpression(table* instance, char const* input) {
  TOKEN token;
  size_t tokenSize;
  char const* tempInput;
  char const* tokenStart;
  input = nextToken(&token, input, &tokenStart, &tokenSize);

  addTableRow(instance);

  if (!input) {
    return 0;
  }
  
  if (token == ID) {
    addTableColumn(instance, tokenStart, tokenSize);
  } else if (token == NUM) {
    if ((tempInput = nextToken(&token, input, &tokenStart, &tokenSize)) && token == ID) {
      addTableColumn(instance, tokenStart, tokenSize);
      input = tempInput;
    } else {
      printf("NUM\n");
    }
  } else {
    printf("Expected ID, NUM or NUM ID near \"%s\"\n", input);
    return 0;
  }
  
  printf("Parsed expression\n");
  
  if ((tempInput = nextToken(&token, input, &tokenStart, &tokenSize)) && (token == PLUS || token == MINUS)) {
    return parseExpression(instance, tempInput);
  } else {
    return input;
  }
}

char const* parseConstraint(table* instance, char const* input) {
  TOKEN token;
  size_t tokenSize;
  char const* tokenStart;

  addTableRow(instance);
  
  input = parseExpression(instance, input);
  if (!input) {
    return 0;
  }
  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  
  if (!input) {
    return 0;
  }
  
  if (token != EQ) {
    printf("Expected equals near %s\n", input);
    return 0;
  }
  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  
  if (!input) {
    return 0;
  }
  
  if (token != NUM) {
    printf("Expected NUM near %s\n", input);
    return 0;
  }
  
  return input;
}

char const* parseConstraints(table* instance, char const* input) {
  TOKEN token;
  size_t tokenSize;
  char const* tempInput;
  char const* tokenStart;
  input = parseConstraint(instance, input);
  
  if (!input) {
    return 0;
  }
  
  if ((tempInput = nextToken(&token, input, &tokenStart, &tokenSize)) && token == COMMA) {
    return parseConstraints(instance, tempInput);
  } else {
    return input;
  }
}

bool parseString(table* instance, char const* input) {
  TOKEN token;
  char const* tokenStart;
  size_t tokenSize;
  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  if (!input) {
    return false;
  }

  if (token != MAX) {
    printf("Expected max to be the next token near %s\n", input);
    return false;
  }
  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  if (!input) {
    return false;
  }
  
  if (token != ID) {
    printf("Expected ID near \"%s\"", input);
    return false;
  }

  addTableColumn(instance, tokenStart, tokenSize);
  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  if (!input) {
    return false;
  }
  
  if (token != EQ) {
    printf("Expected EQ near \"%s\"", input);
    return false;
  }
  
  input = parseExpression(instance, input);
  
  if (!input) {
    return false;
  }
  
  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  if (!input) {
    return false;
  }
  
  if (token == PEOF) {
    return true;
  } else if (token != ST) {
    printf("Expected 's.t.' to be the next token near \"%s\"\n", input);
    return false;
  }
  
  input = parseConstraints(instance, input);
  
  if (!input) {
    return false;
  }

  
  input = nextToken(&token, input, &tokenStart, &tokenSize);
  if (!input) {
    return false;
  }
  
  if (token != PEOF) {
    printf("Unexpected symbol near \"%s\".\n", input);
    return false;
  } else {
    return true;
  }
}

void parserFree() {
  regexFree(&idRegex);
  regexFree(&numRegex);
}
