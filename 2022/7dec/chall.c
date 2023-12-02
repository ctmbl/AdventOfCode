//#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 20
#define MAX_FILES 500

typedef unsigned int index_t;

static char* FILENAME = "input.txt";
static index_t path[MAX_DEPTH]; // stores indexes of dirs in inode, currently in path
static size_t inode[MAX_FILES]; // stores sizes of dirs

void ls(FILE*, index_t);

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* line = NULL;
	size_t i = 0;
	int c = 0;

	index_t wd = -1; // current index in path array
	index_t nd = 0; // current index in 
	while(-1 != (c = getline(&line, &i, input_file))){
		if(strncmp(line, "$ ls", 4) == 0){
			continue;
		} else if(strcmp(line, "$ cd ..\n") == 0){
			wd--;
			if(wd < 0){
				puts("error working dir index < 0");
				exit(1);
			}
		} else if(strncmp(line, "$ cd", 4) == 0){
			wd++;
			if(wd >= MAX_DEPTH){
				puts("error tree folder too deep");
				exit(1);
			}
			path[wd] = nd; 

			if(nd >= MAX_FILES){
				puts("error too many dirs");
				exit(1);
			}
			inode[nd] = 0;
			nd++;
		} else if(strncmp(line, "dir", 3) == 0){
			continue;
		} else if(*line >= '0' && *line <= '9'){
			size_t size;
			sscanf(line, "%d %s\n", &size, NULL);
			//printf("add %d to %d dir\n", size, wd);
			for(index_t k = 0; k <= wd; k++)
				inode[path[k]] += size;
		} else {
			printf("'%s' unknown cmd\n", line);	
			exit(1);
		}
		free(line);
		line = NULL;
		i = 0;
	}
	size_t tot = 0;

	size_t to_delete = inode[0];
	size_t disk_mem =     70000000;
	size_t free_space = disk_mem - inode[0];
	size_t needed_space = 30000000;

	for(index_t k = 0; k <= nd; k++){
		if(inode[k]+free_space >= needed_space && inode[k] < to_delete){
			//printf("%d: %d\n", k, inode[k]);
			to_delete = inode[k];
		}
		if(inode[k] > 100000)
			continue;
		tot = tot + inode[k];
	}
	printf("%d\n%d\n", tot, to_delete);
	fclose(input_file);
	return 0;
}
