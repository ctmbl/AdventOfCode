#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char* FILENAME = "input.txt";

int in(int a, int* list, int n){
	for(int i = 0;i <n; i++){
		if(a == list[i])
			return 1;
	}
	return 0;
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");

	size_t tot = 0;
	char str[5];
	int err = fscanf(input_file, "%s", str);
	assert(err > 0);
	while(strcmp(str, "Card") == 0){
		int i = -1;
		fscanf(input_file, "%d:", &i);
		assert(i != -1 && err);

		int n = 20;
		int* winning_numbers = malloc(n*sizeof(int));
		int k = 0;
		while(1){
			str[0] = 0; // to "reset str" before each scanf
			err = fscanf(input_file, " %s", str);
			printf("DEBUG: '%s'\n", str);
			assert(err > 0);

			int a = atoi(str);
			if(!a)
				break;
			k++;
			if(k>n){
				n*=2;
				realloc(winning_numbers, n);
			}
			winning_numbers[k-1] = a;
		}
		
		int score = 1;
		int m = 0;
		while(1 && m < 50){
			m++;
			str[0] = 0; // to "reset str" before each scanf, then if scnaf encounter EOF a will be 0 and we will break
			err = fscanf(input_file, " %s", str);
			printf("DEBUG: '%s' and err is %d \n", str, err);

			int a = atoi(str);
			if(!a)
				break;

			if(in(a, winning_numbers, k))
				score*=2;
		}
		tot+=score/2; // because we started at 1, in case we don't find any this is an euclidian division so 1/2=0
	}

	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
