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
	
	size_t i = 0;
	int c = 0;
	c = getline(&line, &i, input_file);
	if(c <= 1)
		exit(1);

	char* marker = line;
	size_t k = 1;
	while(*(line+k) != '\0' && *(line+k) != '\n'){
		// check that every character between marker and line+k are diff, increment marker else
		for(char* p = marker; p < line+k; p++){
			if(*p == *(line+k))
				marker = p+1;
		}
		// if we found 4 diff char break
		if(line+k-marker == 4)
			break;
		k++;
	}
	free(line);
	line = NULL;
	i = 0;
	printf("%d\n", k);
	fclose(input_file);
	return 0;
}
