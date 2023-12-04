#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";

int store_line(){

}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* line = NULL;
	size_t buf_size = 0;

	// init lines:
	int len = getline(&line, &buf_size, input_file) - 1; // remove '\n'
	line[len] = '\0';

	printf("%s\n", line);
	return 0;
	char* lines[3];
	for(int j = 0; j<3;j++)
		lines[j] = malloc(sizeof(char) * len + 2);
	memset(lines[0], '.', len+2);
	int i = 1;
	lines[i][0] = '.';
	strcpy(lines[i]+1, line);
	lines[i][len+1] = '.';
	return;
	while(1){
		int len = getline(&line, &buf_size, input_file);
		if(len < 2) // allow to stop on empty lines OR EOF errors
			break;

		if(line[len-1] == '\n'){
			line[len-1] = '\0';
			len--;
		}

		file
		/* code goes here */
	}
	size_t tot = 0;
	free(line);
	line = NULL;
	buf_size = 0;

	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
