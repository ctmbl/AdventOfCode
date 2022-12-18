#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";
typedef struct pos {
	int x;
	int y;
} pos;

static pos head = {0,0};
static pos tail = {0,0};

void move(char dir);
void follow(pos* trace, size_t* tot);

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	pos* trace = NULL;
	char dir = ' ';
	int steps = 0;

	char* line = NULL;
	size_t i = 0;
	int c = 0;
	size_t tot = 0;
	while(-1 != (c = getline(&line, &i, input_file))){
		sscanf(line,"%c %d", &dir, &steps);
		while(steps != 0){
			move(dir);
			follow(trace, &tot);
			steps--;
		}
		
		free(line);
		line = NULL;
		i = 0;
	}
	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}

void move(char dir){
	switch (dir) {
		case 'U': head.y++;
			  break;
		case 'D': head.y--;
			  break;
		case 'R': head.x++;
			  break;
		case 'L': head.x--;
			  break;
		default : printf("'%c' is not a direction\n", dir);
			  break;
	}
	//printf("%d %d\n", head.x, head.y);
}
void follow(pos* trace, size_t* tot){
}
