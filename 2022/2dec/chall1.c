#!/usr/bin/tcc -run

#include <stdio.h>
#include <string.h>

static char* FILENAME = "input.txt";
static char* games[]= {
	"A X",
	"A Y",
	"A Z",
	"B X",
	"B Y",
	"B Z",
	"C X",
	"C Y",
	"C Z",
};
static int pts[] = { 
	4,
	8,
	3,
	1,
	5,
	9,
	7,
	2,
	6,
};

int main(int argc, char** argv){
	puts("ok");
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	
	FILE* input_file = fopen(filename, "r");
	int c = 0;
	int i = 0;
	char* line = NULL;
	while(1){
		if(getline(&line, &i, input_file) != 1){
			line[3] = '\0';
			for(int k=0; k<9; k++){
				if(!strcmp(line, games[k])){
					c+=pts[k];
				}
			}
			continue;			
		}
		break;
	}
	printf("points: %d\n", c);
	fclose(input_file);
	puts("ok");
	return 0;
}
