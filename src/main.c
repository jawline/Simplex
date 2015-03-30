#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv) {
	parserInit();
	parseString("max 5 s.t. 5x + 4x = 5");
	parserFree();
}