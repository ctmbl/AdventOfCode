//#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char* FILENAME = "input.txt";

int (*hand_type)(char*);
int (*strength)(char);

typedef struct {
	char cards[6];
	int rank;
	int bid;
} hand;



int strength_part1(char c){
	switch (c)
	{
	case 'A':
		return 14;
	case 'K':
		return 13;
	case 'Q':
		return 12;
	case 'J':
		return 11;
	case 'T':
		return 10;
	default:
		char str[2] = {c, 0};
		return atoi(str);
	}
}


int strength_part2(char c){
	switch (c)
	{
	case 'A':
		return 13; // 14 -> 13
	case 'K':
		return 12; // 13 -> 12
	case 'Q':
		return 11; // 12 -> 11
	case 'J':
		return 1; // Jokers are now the weakest cards
	case 'T':
		return 10;
	default:
		char str[2] = {c, 0};
		return atoi(str);
	}
}


int imax(int* l, int n){
	int i_max = 0;
	for (int i = 1; i < n; i++){
		if(l[i] > l[i_max]){
			i_max = i;
		}
	}
	return i_max;
}


int hand_type_part1(char h[6]){
	if(h[0] == 0){
		return 0;
	}
	int numbers_of_cards[13];
	for(int i = 0; i<13; i++)
		numbers_of_cards[i] = 0;

	for(int i = 0; i<=4; i++){
		numbers_of_cards[strength(h[i]) - 2]++;
	}
	int i_max = imax(numbers_of_cards, 13);
	int cardmax = numbers_of_cards[i_max];
	// for(int i = 0; i<13; i++)
	// 	printf("%d ", numbers_of_cards[i]);
	// printf("\n");
	// printf("imax %d; card max %d \n", i_max, cardmax);
	switch (cardmax)
	{
	case 1: // high card
		return 1;
	case 2: // at least a pair
		numbers_of_cards[i_max] = 0;
		i_max = imax(numbers_of_cards, 13);
		if(numbers_of_cards[i_max] == 2)
			return 3;  // two pairs!
		return 2; // only one pair...
	case 3: // three of a kind or full house
		numbers_of_cards[i_max] = 0;
		i_max = imax(numbers_of_cards, 13);
		if(numbers_of_cards[i_max] == 2)
			return 5; // full house!
		return 4; // only three of a kind
	default:
		return numbers_of_cards[i_max] + 2; // four --> 6 ; five --> 7 (of a kind)
	}
}


int hand_type_part2(char h[6]){
	if(h[0] == 0){
		return 0;
	}
	int numbers_of_cards[13];
	for(int i = 0; i<13; i++)
		numbers_of_cards[i] = 0;

	for(int i = 0; i<=4; i++){
		numbers_of_cards[strength(h[i]) - 1]++;
	}
	int nb_jokers = numbers_of_cards[0];
	numbers_of_cards[0] = 0; // we don't want to count pairs of jokers or so, we'll deal with them later

	int i_max = imax(numbers_of_cards, 13);
	int score = 0;
	// for(int i = 0; i<13; i++)
	// 	printf("%d ", numbers_of_cards[i]);
	// printf("\n");
	// printf("imax %d; card max %d \n", i_max, numbers_of_cards[i_max]);

	switch (numbers_of_cards[i_max])
	{
	case 0: // we got all jokers!
		score = 0;
		break;
	case 1: // high card
		score = 1;
		break;
	case 2: // at least a pair
		numbers_of_cards[i_max] = 0;
		i_max = imax(numbers_of_cards, 13);
		if(numbers_of_cards[i_max] == 2)
			score = 3;  // two pairs!
		else 
			score = 2; // only one pair...
		break;
	case 3: // three of a kind or full house
		numbers_of_cards[i_max] = 0;
		i_max = imax(numbers_of_cards, 13);
		if(numbers_of_cards[i_max] == 2)
			score = 5; // full house!
		else
			score = 4; // only three of a kind
		break;
	default:
		score = numbers_of_cards[i_max] + 2; // four of a kind --> 6 ; five of a kind --> 7 
	}

	// now we deal with jokers:
	while(nb_jokers){ // if there are jokers
		switch (score)
		{
		case 2: // if you have a pair, making a three of kind earns more points than a double pair
		case 3: // if you have a double pair, making a full house is the best option
		case 4: // if you have a three of a kind making a four earns more points than a full house
			score += 2;
			break;
		
		default:
			score += 1;
			break;
		}
		nb_jokers--;
	}
	return score;
}


int better_than(char left[6], char right[6]){
	int ltype = hand_type(left);
	int rtype = hand_type(right);
	//printf("%s %d; %s %d\n", left, ltype, right, rtype);
	if(rtype != ltype){
		return ltype > rtype;
	}
	int card = 0;
	while(left[card] == right[card]){
		//printf("%d\n", card);
		card++;
	}
	return strength(left[card]) > strength(right[card]);
}


int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");
	hand_type = hand_type_part1;
	strength = strength_part1;

	size_t tot = 0;
	size_t n = 0;
	size_t MAX_HANDS = 100;
	hand* hands = malloc(MAX_HANDS * sizeof(hand));

	assert(hand_type("\0    ") == 0);
	assert(hand_type("AKQT9") == 1);
	assert(hand_type("AAQT9") == 2);
	assert(hand_type("AAQQ9") == 3);
	assert(hand_type("AAAT9") == 4);
	assert(hand_type("AAATT") == 5);
	assert(hand_type("AAAA9") == 6);
	assert(hand_type("AAAAA") == 7);

	// not exhaustive but better than nothing!
	if(hand_type == hand_type_part2 && strength == strength_part2){
		assert(hand_type("AKQTJ") == 2);
		assert(hand_type("AKQJJ") == 4);
		assert(hand_type("AKJJJ") == 6);
		assert(hand_type("AJJJJ") == 7);
		assert(hand_type("JJJJJ") == 7);
	}

	int err = 0;
	do{
		if(n >= MAX_HANDS){
			MAX_HANDS *= 2;
			hands = realloc(hands, sizeof(hand) * MAX_HANDS);
		}
		err = fscanf(input_file, "%5s %d", hands[n].cards, &(hands[n].bid));
		printf("err: %d; hand: %s %d\n", err, hands[n].cards, hands[n].bid);
		n++;
	}while(err > 0);
	n--;

    for(int p = n; p >= 1; p--){

        hand* stronger_hand = hands;
        for (size_t i = 0; i<n; i++){
			if(strcmp(hands[i].cards, stronger_hand->cards) == 0){
				continue;
			}
			if (better_than(hands[i].cards, stronger_hand->cards)){
				stronger_hand = hands+i;
			}
        }
        stronger_hand->rank = p;
		stronger_hand->cards[0] = 0;
		tot += stronger_hand->rank * stronger_hand->bid;
		printf("stronger: %d, tot: %ld\n", stronger_hand->bid, tot);

    }

	printf("%ld\n", tot);
	fclose(input_file);
	free(hands);
	return 0;
}
