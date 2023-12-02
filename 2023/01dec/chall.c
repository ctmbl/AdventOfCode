#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//static char* FILENAME = "input.ex.txt";
static char* FILENAME = "input.txt";

int is_digit_part1(char* c, char* d){
	if(isdigit(*c)){
		*d = *c;
		//printf("DEBUG: found digit it's %c\n", *d);
		return 1;
	}
	return 0;
}

int is_digit_in_letters(char* c, char* d){
	char digits[9][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	for(int i = 0; i < 9; i++){
		if(strncmp(digits[i], c, strlen(digits[i])) == 0){
			*d = (char)0x31+i;
			//printf("DEBUG: found digit in letters: %s == %c\n", c, *d);
			return 1;
		}
	}
	return 0;
}

int is_digit_part2(char* c, char* d){
	return is_digit_part1(c, d) || is_digit_in_letters(c, d);
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* line = NULL;
	size_t i = 0;
	int c = 0;
	size_t tot = 0;
	while(1){
		c = getline(&line, &i, input_file);
		if(c == -1)
			break;

		char* start = line;
		char* end = line + strlen(line)-1 -1;
		//printf("\nDEBUG: line:=%s - start: '%c' - end '%c'\n", line, *start, *end);

		int (*is_digit)(char*,char*);
		// CHOOSE PART 1 or PART 2 HERE:
		//is_digit = is_digit_part1;
		is_digit = is_digit_part2;

		char d1 = 0;
		char d2 = 0;
		while(1){
			if(!d1 && !is_digit(start, &d1)){
				start++;
				continue;
			}
			//printf("DEBUG: found start=%c\n", d1);

			if(!d2 && !is_digit(end, &d2)){
				end--;
				continue;
			}
			//printf("DEBUG: found end=%c\n", d2);
			
			//printf("DEBUG: line after modif: %s\n", line);
			break;
		}
		char nb[3] = {'a','a', '\0'};
		nb[0] = d1;
		nb[1] = d2;
		//printf("DEBUG nb=%s\n", nb);
		//printf("DEBUG: %d = %d + %s\n", tot+ atoi(nb), tot, nb );

		tot += atoi(nb);

		free(line);
		line = NULL;
		i = 0;
	}
	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
