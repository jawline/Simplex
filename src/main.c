#include <stdio.h>
#include "parser.h"
#include "solver.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: %s max problem\n", argv[0]);
		return -1;
	}

	table instance;
	simplex_result results;
	
	parserInit();
	
	initialiseTable(&instance);
	if (parseString(&instance, argv[1])) {
		printTable(&instance);
	} else {
		printf("Failed to parse table. Exit\n");
		return -1;
	}
	solveTable(&instance, &results);

	printf("Results: %f\n", results.value);

	freeTable(&instance);
	parserFree();
	return 0;
}
