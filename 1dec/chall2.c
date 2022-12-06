#!/usr/bin/tcc -run

#include <stdio.h>
#include <string.h>

char* FILENAME = "input.txt";

typedef struct elf {
	int num;
	int energy;
} elf;

static elf top_elfs[] = { {0,0}, {0,0}, {0,0}, };

void update_if_better(elf* current) {
	if (current->energy < top_elfs[0].energy) {
		return;
	}
	printf("elf %d carries %d energy > %d from older lighter elf\n", current->num, current->energy, top_elfs[0].energy);
	top_elfs[0].energy = current->energy;
	top_elfs[0].num = current->num;
	if (top_elfs[0].energy < top_elfs[1].energy)
		goto end;

	elf temp = top_elfs[1];
	top_elfs[1] = top_elfs[0];
	top_elfs[0] = temp;
	if (top_elfs[1].energy < top_elfs[2].energy)
		goto end;

	temp = top_elfs[2];
	top_elfs[2] = top_elfs[1];
	top_elfs[1] = temp;
end:	
	printf("status: 0: %d; 1: %d; 2: %d\n", top_elfs[0].energy, top_elfs[1].energy, top_elfs[2].energy);
}

int main(int argc, char** argv){
	printf("works\n");
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	int c = 0;
	elf current = {
		.num = 0,
		.energy = 0
	};

	puts("First elf coming");
	while (1) {
		char* line = NULL;
		int i = 0;
		char* endptr = NULL;
		c = getline(&line, &i, input_file);
		if (c == 1 || c == -1) {
			update_if_better(&current);
			current.energy = 0;
			current.num++;
			if (c == -1)
				break;
			puts("New elf coming");
		} else {
			current.energy += strtoul(line, &endptr, 10);
		}
	}
	int sum = top_elfs[0].energy + top_elfs[1].energy + top_elfs[2].energy;
	printf("elf %d, %d and %d carry the most energy: %d in total\n", top_elfs[0].num, top_elfs[1].num, top_elfs[2].num, sum);
	fclose(input_file);
	return 0;
}
