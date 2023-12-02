#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";

char* word(char** stacks, int n);
int count(char* str, char chr);

char** init(FILE* stream, int* n){
	char* lines = NULL;
	size_t i = 0;
	ssize_t c = getdelim(&lines, &i, 0x31, stream);

	char* list = NULL;
	i = 0;
	getline(&list, &i, stream);

	char* end = list+strlen(list)-1;
	end -= 2;
	while (*(end-1) != ' ')
		end--;
	printf("nb of stack: %s\n",end);
	int n_stacks = strtoul(end, &end, 10);
	*n = n_stacks;

	char** stacks = malloc(sizeof(char*) * n_stacks);
	int n_lines = count(lines, '\n');
	for(int k = 0; k<n_stacks; k++){
		int size = sizeof(char) * n_stacks * n_lines;
		stacks[k] = malloc(size);
		memset(stacks[k],0, size);
	}
	
	printf("%s\n", lines+1);
	int col = 0;
	int row = 0;
	while(row <= n_lines-1){
		lines++;
		if(*lines != ' ')
			stacks[col][n_lines-row-1] = *lines;
		lines+=2;
		if(*lines == '\n'){
			col = 0;
			row++;
		} else
			col++;
		lines++;
		//printf("'%c' %d \n",*(lines+1), row);
	}
	for(int k = 0; k<n_stacks; k++)
		stacks[k] += strlen(stacks[k])-1;
	printf("pointer on stack 3: %s\n", stacks[2]);

	return stacks;
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* line = NULL;
	size_t i = 0;
	ssize_t c = 0;
	int n_stacks = 0;
	char** stacks = init(input_file, &n_stacks);
	while(1){
		c = getline(&line, &i, input_file);
		char* save = line;
		if(c == -1)
			break;
		line+=5;
		int nb = strtoul(line, &line, 10);
		line += 6;
		int from = strtoul(line, &line, 10) - 1;
		line += 4;
		int to = strtoul(line, &line, 10) - 1;
	
		while(nb!=0){
			*(++stacks[to]) = *(stacks[from]--);
			nb--;
		}

		free(save);
		line = NULL;
		i = 0;
	}
	printf("%s\n", word(stacks, n_stacks));
	fclose(input_file);
	return 0;
}

char* word(char** stacks, int n){
	char* w = malloc(sizeof(char) * n);
	n--;
	while(n>=0){
		w[n] = *(stacks[n]);
		n--;
	}
	return w;
}

int count(char* str, char chr){
	int i = 0;
	while(*(++str) != '\0'){
		if(*str == chr)
			i++;
	}
	return i;
}
