#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* FILENAME = "input.txt";

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

	int RED = 12;
	int GREEN = 13;
	int BLUE = 14;
	while(1){
		c = getline(&line, &i, input_file);
		if(c == -1)
			break;
		int len = strlen(line);
		if(line[len-1] == '\n')
			line[len-1] = '\0';

		printf("DEBUG: line: %s\n", line);
		char* game_str = strchr(line, ':');
		*game_str = '\0';
		game_str++;

		int id = -1;
		sscanf(line, "Game %d", &id);

		printf("DEBUG: ID: %d - game: %s\n", id, game_str);

		char* ptr = game_str;
		int n = 0; // number of sets in the game
		char** sets = malloc(sizeof(char*) * 50);

		sets[n] = ptr;
		//printf("DEBUG: added '%s' to the sets of game %d\n", sets[n], id);
		while(*ptr){
			if(*ptr == ';'){
				*ptr = '\0';
				ptr++;
				n++;
				sets[n] = ptr;
				//printf("DEBUG: added '%s' to the sets of game %d\n", sets[n], id);
				continue;
			}
			if(*ptr == ',')
				*ptr=' ';
			ptr++;

			//printf("DEBUG: remains: %s\n", ptr);
		}
		n++; // because n is the SIZE of sets (nb of sets in this game)
		printf("DEBUG: there are %d sets in this game\n", n);
		for(int i = 0; i < n; i++){
			int nb;
			char* color;
			sscanf(sets[i], " %d %ms", &nb, &color);
			printf("DEBUG: '%s' is '%d' '%s' balls\n", sets[i], nb, color);
		}
		break;
		tot += id;
		free(line);
		line = NULL;
		i = 0;
	}
	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
