#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: %s max problem\n", argv[0]);
		return -1;
	}

	parserInit();
	parseString(argv[1]);
	parserFree();
}