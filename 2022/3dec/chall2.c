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
	char* lines[3] = {NULL, NULL, NULL};
	int c = 0;
	int i = 0;
	int tot = 0;
	while(1){
		for(int k = 0; k<3; k++)
			c = getline(lines+k, &i, input_file);
		if(c == -1)
			break;
		for(int k = 0; k < c-1; k++){
			char chr = lines[2][k];
			if(in(chr, lines[1]) && in(chr, lines[0])){
				char chr_str[2] = {chr, '\0'};
				tot += strcspn(alphabet, chr_str)+1;
				break;
			}
		}
		for(int k = 0; k<3; k++){
			free(lines[k]);
			lines[k] = NULL;
		}
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
