//#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char* FILENAME = "input.txt";

typedef struct{
	char name[4];
	char next[2][4];
} node;

node* search(node* l, int n, char node[4]){
//	printf("search %s ", node);
	for(int i = 0; i < n ; i++){
		if(strcmp(node, l[i].name) == 0){
//			printf("found it: %s %s %s \n", l[i].name, l[i].next[0], l[i].next[1]);
			return l+i;
		}
	}
//	printf("didn't found it\n");
	return NULL;
}


int all_Z(node** l, size_t n){
	for(size_t i = 0; i < n; i++){
		if(l[i]->name[2] != 'Z'){
//			printf("Sorry %s is not Z terminated, it was the %ld/%ld\n", l[i]->name, i, n);
			return 0;
		}
	}
	return 1;
}


int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");

	size_t tot = 0;
	size_t n = 0;
	size_t MAX_NODES = 100;
	node* nodes = malloc(MAX_NODES * sizeof(node));

	size_t startings = 0;
	size_t MAX_STARTINGS = 100;
	node** cur_list = malloc(MAX_STARTINGS * sizeof(node));

	char* c_dir;
	fscanf(input_file, "%ms", &c_dir);
	size_t nb_dir = strlen(c_dir);
	__uint8_t* dir = malloc(sizeof(__uint8_t) * nb_dir);
	for(int i = 0; i < nb_dir; i++){
		dir[i] = 1 ? c_dir[i] == 'R' : 0;
	}
	free(c_dir);

	int err = 0;
	do{
		if(n >= MAX_NODES){
			MAX_NODES *= 2;
			nodes = realloc(nodes, sizeof(node) * MAX_NODES);
		}
		err = fscanf(input_file, "%3s  = (%3s, %3s)", nodes[n].name, nodes[n].next[0], nodes[n].next[1]);
//		printf("err: %d; node: %s L: %s R: %s\n", err, nodes[n].name, nodes[n].next[0], nodes[n].next[1]);

		if(nodes[n].name[2] == 'A'){
			if(startings >= MAX_STARTINGS){
				MAX_STARTINGS *= 2;
				cur_list = realloc(cur_list, sizeof(node**) * MAX_STARTINGS);
			}
			cur_list[startings] = nodes+n;
			startings++;
		}
		n++;
	}while(err > 0);
	n--;

	node* cur = search(nodes, n, "AAA");
    while(strcmp(cur->name, "ZZZ") != 0){
               cur = search(nodes, n, cur->next[dir[tot%nb_dir]]);
               assert(cur);
               tot++;
	}
	printf("Part1: %ld\n", tot);

	tot = 0;
	printf("Part2: The answer is the PPCM of: ");
	for(size_t i = 0; i < startings; i++){
		cur = cur_list[i];
    	while(cur->name[2] != 'Z'){
			cur = search(nodes, n, cur->next[dir[tot%nb_dir]]);
			assert(cur);
			tot++;
		}
		printf("%ld ", tot);
		tot = 0;
	}
	printf("\n");
	printf("I've got a life and something else to do than coding a PPCM in C so: https://www.dcode.fr/ppcm\n");
	fclose(input_file);
	free(dir);
	return 0;
}
