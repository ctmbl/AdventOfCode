#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";
typedef struct forest {
	char** trees;
	size_t width;
	size_t height;
} forest_t;
typedef unsigned short tree_t;

void visible_trees(forest_t* forest, size_t* trees, size_t* scenic_score);

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	forest_t forest = {NULL,0,0};
	size_t h = 0;

	char* line = NULL;
	size_t i = 0;
	int c = 0;
	while(-1 != (c = getline(&line, &i, input_file))){
		line[c-1] = '\0';
		h++;
		forest.trees = realloc(forest.trees, h*sizeof(char*));
		forest.trees[h-1] = line;

		line = NULL;
		i = 0;
	}
	forest.width = strlen(forest.trees[0]);
	forest.height = h;
	//printf("h: %d, w: %d\n", forest.height, forest.width);
	//printf("trees[3]=%s\n", forest.trees[3]);
	size_t trees = 0;
	size_t scenic_score = 0;
	visible_trees(&forest, &trees, &scenic_score);
	printf("part1: %d\npart2: %d\n", trees, scenic_score);
	fclose(input_file);
	return 0;
}

size_t visible(forest_t* forest, size_t start_i, size_t start_j, size_t* score){
	size_t is_visible = 0;
	tree_t tree = forest->trees[start_i][start_j];
	//printf("tree[%d][%d] = %c\n", start_i, start_j, tree);
	goto south;
south:
	for(size_t i = start_i+1; i < forest->height; i++){
		//printf("tree[%d][%d] = %c\n", i, start_j, forest->trees[i][start_j]);
		if(forest->trees[i][start_j] >= tree){
			*score *= (i-start_i);
			goto north;
		}
	}
	*score *= (forest->height-start_i-1);
	is_visible = 1;
north:
	for(int i = (int)start_i-1; i >= 0; i--){
		if(forest->trees[i][start_j] >= tree){
			*score *= (start_i-i);
			goto east;
		}
	}
	*score *= (start_i);
	is_visible = 1;
east:
	for(size_t j = start_j+1; j < forest->width; j++){
		if(forest->trees[start_i][j] >= tree){
			*score *= (j-start_j);
			goto west;
		}
	}
	*score *= (forest->width-start_j-1);
	is_visible = 1;
west:
	for(int j = (int)start_j-1; j >= 0; j--){
		if(forest->trees[start_i][j] >= tree){
			*score *= (start_j-j);
			goto no;
		}
	}
	*score *= (start_j);
	is_visible = 1;
no:
	return is_visible;
}

void visible_trees(forest_t* forest, size_t* trees, size_t* scenic_score){
	for(size_t i = 0; i < forest->height; i++){
		for(size_t j = 0; j < forest->width; j++){
			size_t score = 1;
			*trees += visible(forest, i, j, &score);
			if(score > *scenic_score){
				*scenic_score = score;
			}
		}
	}
}
