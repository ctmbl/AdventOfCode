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
	size_t NB_LINES = 20;
	int* nb_cards = malloc(sizeof(int)*NB_LINES);
	for(int i = 0; i < NB_LINES; i++)
		nb_cards[i] = 1;
	int card = 0;	

	char str[5];
	int err = fscanf(input_file, "%s", str);
	assert(err > 0);
	while(strcmp(str, "Card") == 0){
		int i = -1;
		err = fscanf(input_file, "%d:", &i);

		assert(i != -1 && err);
		assert(card+1 == i);

		size_t n = 20;
		int* winning_numbers = malloc(n*sizeof(int));

		int k = 0;
		int m = 0; // a security

		while(1 && m < 2000){
			m++;
			str[0] = 0; // to "reset str" before each scanf
			err = fscanf(input_file, " %s", str);
			//printf("DEBUG: '%s'\n", str);
			assert(err > 0);

			int a = atoi(str);
			if(!a)
				break;
			k++;
			if(k>n){
				n*=2;
				winning_numbers = realloc(winning_numbers, n*sizeof(int));

				assert(winning_numbers);
			}
			winning_numbers[k-1] = a;
		}
		
		// // Part1:
		//int score = 1;
		int score = 0;
		m = 0;
		while(1 && m < 2000){
			m++;
			str[0] = 0; // to "reset str" before each scanf, then if scnaf encounter EOF a will be 0 and we will break
			err = fscanf(input_file, " %s", str);
			//printf("DEBUG: '%s' and err is %d \n", str, err);

			int a = atoi(str);
			if(!a)
				break;

			// // Part1:
			// if(in(a, winning_numbers, k))
			// 	score*=2;
			if(in(a, winning_numbers, k))
				score++;
		}
		if(card+score+1 > NB_LINES){
			nb_cards = realloc(nb_cards, NB_LINES*2*sizeof(int));
			assert(nb_cards);
			for(int j = NB_LINES; j < NB_LINES*2; j++)
				nb_cards[j] = 1;
			NB_LINES *= 2;
		}

		for(int j = 1; j <= score; j++)
			nb_cards[card+j] += nb_cards[card];
		// // Part1:
		//tot+=score/2; // because we started at 1, in case we don't find any this is an euclidian division so 1/2=0
		printf("DEBUG: Card %d: score = %d\n", card, score);
		tot+= nb_cards[card];
		card++;
		free(winning_numbers);
	}
	free(nb_cards);

	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
