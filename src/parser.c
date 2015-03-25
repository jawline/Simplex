#include "parser.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * Skip whitespace until the end of the input or the next character is found
 */
char const* nextToken(char const* input) {
  for (; *input && isspace(*input); input++) {}
  return input;
}
