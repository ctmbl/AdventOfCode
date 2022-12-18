#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static char* FILENAME = "input.txt";
typedef struct pos {
	int x;
	int y;
} pos;

static pos head = {0,0};
static pos tail = {0,0};

void move(char dir);
pos* follow(pos* trace, size_t* tot);

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
			trace = follow(trace, &tot);
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
	printf("%d %d\n", head.x, head.y);
}
static bool in(pos p, pos* list, int length){
	if(list == NULL)
		return false;
	printf("last item: %d %d\n", list[length-1].x, list[length-1].y);
	for(int k = 0; k < length; k++){
		if(p.x == list[k].x && p.y == list[k].y)
			return true;
	}
	return false;
}
pos* follow(pos* trace, size_t* tot){
	int dec_x = abs(head.x - tail.x);
	int dec_y = abs(head.y - tail.y);
	bool way_x = head.x > tail.x ? 1 : -1;
	bool way_y = head.y > tail.y ? 1 : -1;
	if(dec_x <= 1 && dec_y <= 1){
		return trace;
	}

	if(dec_y >= 2){
		if(dec_x >= 1)
			tail.x += way_x;
		tail.y += way_y;
	}
	if(dec_x >= 2){
		if(dec_y >= 1)
			tail.y += way_y;
		tail.x += way_x;
	}

	if(in(tail, trace, *tot)){
		return trace;
	}
	(*tot)++;
	trace = realloc(trace, (*tot) * sizeof(pos));
	trace[(*tot)-1].x = tail.x;
	trace[(*tot)-1].y = tail.y;
	printf("added %d %d, tot=%d\n", trace[(*tot)-1].x,trace[(*tot)-1].y, *tot);
	return trace;
}
