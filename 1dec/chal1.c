#!/usr/bin/tcc -run

#include <stdio.h>
#include <string.h>

char* FILENAME = "input.txt";

typedef struct elf {
	int num;
	int energy;
} elf;

int main(int argc, char** argv){
	printf("works\n");
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	int c = 0;
	elf max = {
		.num = 0,
		.energy = 0
	};
	elf current = {
		.num = 0,
		.energy = 0
	};

	puts("First elf coming\n");
	while (1) {
		char* line = NULL;
		int i = 0;
		char* endptr = NULL;
		c = getline(&line, &i, input_file);
		if (c == 1 || c == -1) {
			if (current.energy > max.energy) {
				printf("elf %d carries %d energy > %d from older max elf\n", current.num, current.energy, max.energy);
				max.energy = current.energy;
				max.num = current.num;
			}
			current.energy = 0;
			current.num++;
			if (c == -1)
				break;
			puts("New elf coming\n");
		} else {
			current.energy += strtoul(line, &endptr, 10);
		}
	}
	printf("elf %d carries the most energy: %d\n", max.num, max.energy);
	fclose(input_file);
	return 0;
}
