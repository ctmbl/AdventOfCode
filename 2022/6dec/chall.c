#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";

static inline packet_start(){
}

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

	size_t packet_start = 0;
	size_t msg_start = 0;
	size_t curr = 0;
	size_t k = 1;
	while(*(line+k) != '\0' && *(line+k) != '\n' && !(packet_start && msg_start)){
		// check that every character between line+curr and line+k are diff, increment curr else
		for(size_t p = curr; p < k; p++){
			if(*(line+p) == *(line+k))
				curr = p+1;
		}
		// if we found 4 diff chars found packet_start
		if(k-curr+1 == 4 && !packet_start)
			packet_start = k+1;
		
		if(k-curr+1 == 14 && !msg_start)
			msg_start = k+1;
		k++;
	}
	free(line);
	line = NULL;
	i = 0;
	printf("%d\n%d\n", packet_start, msg_start);
	fclose(input_file);
	return 0;
}
