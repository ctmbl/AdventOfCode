#!/usr/bin/tcc -run

#include <stdio.h>
#include <string.h>

char* FILENAME = "input.txt";

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	fclose(input_file);
	return 0;
}
