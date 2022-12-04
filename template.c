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
	char* line = NULL;
	int i = 0;
	int c = 0;
	while(1){
		c = getline(&line, &i, input_file);
		if(c == -1)
			break;
	}
	fclose(input_file);
	return 0;
}
