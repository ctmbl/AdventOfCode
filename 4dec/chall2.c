#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";

typedef struct range {
	unsigned long a;
	unsigned long b;
} range;

int included(range* g, range* d){
	if((d->a <= g->b) && (d->a >= g->a))
		return 1;
	if((g->a <= d->b) && (g->a >= d->a))
		return 1;
	return 0;
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* line = NULL;
	char* save = NULL;
	int i = 0;
	int c = 0;
	int tot = 0;
	char* dash = "-";
	char* comma = ",";
	char* ptr = NULL;
	range range1;
	range range2;
	while(1){
		c = getline(&line, &i, input_file);
		if(c == -1)
			break;
		save= line;
		range1.a = strtoul(line, &line, 10);
		line++;
		range1.b = strtoul(line, &line, 10);
		line++;
		range2.a = strtoul(line, &line, 10);
		line++;
		range2.b = strtoul(line, &line, 10);

		int x = included(&range1, &range2);
		if(x == 1)
			printf("line: %s %d-%d,%d-%d\n\n", save, range1.a, range1.b, range2.a, range2.b);
		tot += x;

		free(save);
		line = NULL;
		i = 0;
	}
	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
