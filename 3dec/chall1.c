#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* FILENAME = "input.txt";

bool in(char chr, char* str);

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
		c--;
		line[c] = '\0';
		if(strlen(line)%2 != 0){
			puts("error on line length!!!!");
			exit(1);
		}


		free(line);
		line = NULL;
	}
	fclose(input_file);
	return 0;
}

bool in(char chr, char* str){
       for(char* c = str; *c != '\0'; c++){
	       if(*c == chr)
		       return true;
       }
       return false;
}
