#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* line = NULL;
	size_t buf_size = 0;

	size_t tot = 0;
	while(1){
		int len = getline(&line, &buf_size, input_file);
		if(len < 2) // allow to stop on empty lines OR and EOF errors
			break;

		if(line[len-1] == '\n'){
			line[len-1] = '\0';
			len--;
		}

		/* code goes here */
	}
	free(line);
	line = NULL;
	buf_size = 0;

	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
