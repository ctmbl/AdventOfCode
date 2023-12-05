#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char* FILENAME = "input.txt";
static int len = 0;

void init_lines(char** lines, char* buf){
	// init lines:
	for(int j = 0; j<3;j++){
		lines[j] = malloc(sizeof(char) * len + 3); // len of line + starting '.' and ending '.', with 1 bytes for the null terminating
		lines[j][len+2] = 0; // null terminating byte
	}
	// init lines[0] to full points
	memset(lines[0], '.', len+2);

	// copy first line of the file to lines[1]
	lines[1][0] = '.';
	strcpy(lines[1]+1, buf);
	lines[1][len+1] = '.';

	// init lines[2][0] because we won't be touching it again
	lines[2][0] = '.';

}

void print_lines(char* lines[3]){
	printf("\nDEBUG:\n%.*s\n%.*s\n%.*s\n", len, lines[0], len, lines[1], len, lines[2]);
}

inline int check_line(char* line, int part_len){
	// line must be the pointer to the character above/below the beginning of the part (because we access -1)
	for(int l = -1; l < part_len+1; l++){	
		if(line[l] != '.')
			return 1;
	}
	return 0;
}

int look_neighbors(char** lines, int k, int j, int part_len){
	return (lines[k][j-1] != '.') | 
		   (lines[k][j+part_len] != '.') | 
		   check_line(lines[(k+3-1)%3]+j, part_len) |
		   check_line(lines[(k+1)%3]+j, part_len);
}

void handle_line1(char** lines, int k, int* p_tot){
	for(int j = 1; j < len+1; j++){ // starts at 1 and stop at len: ..45.. head and tail . are fillers
		if(!isdigit(lines[k][j]))
			continue;

		char* endptr;
		int part = strtol(lines[k]+j, &endptr, 10);
		//printf("DEBUG: endptr: %p %d ; startptr %p %d \n", endptr, endptr, lines[k]+j, lines[k]+j);
		int part_len = (int)endptr-(int)(lines[k]+j);
		printf("DEBUG: part: %d; length %d\n", part, part_len);
		*p_tot += look_neighbors(lines, k, j, part_len) * part;
		j+=part_len;
	}
}

void find_part_start(char** part){
	while(isdigit(*(*part-1)))
		(*part)--;
}

void handle_line2(char** lines, int k, int* p_tot){
	for(int j = 1; j < len+1; j++){ // starts at 1 and stop at len: ..45.. head and tail . are fillers
		if(lines[k][j] != '*')
			continue;

		char* parts[2] = {NULL,NULL};
		int i = 0;
		for(int m = -1; m <= 1; m++){
			int mm = (m+k+3)%3; // probably useless we could study with 0<= m <=2 it should work too
			for(char* ptr = lines[mm]+j-1; ptr <= lines[mm]+j+1; ptr++){
				if(isdigit(*ptr)){
					strtol(ptr, &ptr, 10);
					parts[i] = ptr;
					i++;
				}
			}
		}
		if(i > 2)
			exit(13);
		if(i < 2)
			continue;

		find_part_start(parts);
		find_part_start(parts+1);

		int part1 = atoi(parts[0]);
		int part2 = atoi(parts[1]);
		printf("DEBUG: found a gear and 2 parts: %d and %d\n", part1, part2);
		*p_tot += part1*part2;
	}
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	char* buf = NULL;
	size_t buf_size = 0;

	// get first line and line length:
	len = getline(&buf, &buf_size, input_file);
	buf[len] = '\0';
	len--; // remove '\n'

	char* lines[3];
	init_lines(lines, buf);
	print_lines(lines);

	// we don't need this buf anymore, we'll now read directly into lines
	free(buf);
	buf = NULL;
	buf_size = 0;

	int i = 2; // row in lines to write to
	int n = 1; // total nb of rows
	size_t tot = 0;

	void (*handle_line)(char**, int, int*) = handle_line2; // choose part 1 or 2
	while(1){
		buf = fgets(lines[i]+1, len+2, input_file);
		if(!buf) // allow to stop on empty lines OR EOF errors
			break;
		assert(buf == lines[i]+1);

		lines[i][len+1] = '.'; // replace (if there is one) the '\n' by a dot

		print_lines(lines);
		int k = (3+i-1)%3; // the row to study
		handle_line(lines, k, &tot);
		
		i = (i+1)%3; // next row to write to
		n++; // total number of rows
	}
	memset(lines[i], '.', len+2); // set the last line to full dots
	handle_line(lines, (3+i-1)%3, &tot); // handle the last line
	printf("DEBUG: there was %d rows \n", n);

	printf("%d\n", tot);

	// free lines and close file
	for(int j = 0; j<3;j++){
		free(lines[j]);
		lines[j] = NULL;
	}
	fclose(input_file);
	return 0;
}
