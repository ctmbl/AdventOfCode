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
	for(int i = 0; i < n ; i++){
		if(strcmp(node, l[i].name) == 0)
			return l+i;
	}
	return NULL;
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
		printf("err: %d; node: %s L: %s R: %s\n", err, nodes[n].name, nodes[n].next[0], nodes[n].next[1]);
		n++;
	}while(err > 0);
	n--;

	node* cur = search(nodes, n, "AAA");
    while(strcmp(cur->name, "ZZZ") != 0){
		cur = search(nodes, n, cur->next[dir[tot%nb_dir]]);
		assert(cur);
		tot++;
	}

	printf("%ld\n", tot);
	fclose(input_file);
	free(dir);
	return 0;
}
