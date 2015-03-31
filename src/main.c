#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: %s max problem\n", argv[0]);
		return -1;
	}

	table instance;
	initialiseTable(&instance);

	parserInit();
	parseString(&instance, argv[1]);
	parserFree();

	freeTable(&instance);
}