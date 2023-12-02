#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static char* FILENAME = "input.txt";
static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
	int tot = 0;
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
		int mid = (int)(c/2);
		for(int k = 0; k < mid; k++){
			if(in(line[k], (line+mid))){
				char chr[2] = {*(line+k), '\0'};
				tot += strcspn(alphabet, chr)+1;
				break;
			}
		}
		free(line);
		line = NULL;
	}
	printf("total: %d\n", tot);
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
