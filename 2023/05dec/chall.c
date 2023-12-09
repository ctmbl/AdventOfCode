//#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

static char* FILENAME = "input.txt";
FILE* input_file = NULL;

typedef struct{
	unsigned src;
	unsigned dest;
	unsigned range;
} node;

int read_map(node* map){
	int it = 0;
	int err = 0;
	do{
		err = fscanf(input_file, "%u %u %u", &map[it].dest, &map[it].src, &map[it].range);
		//printf("err: %d; node: %u src: %u dest: %u range: %u\n", err, it, map[it].src, map[it].dest, map[it].range);
		it++;
	}while(err == 3);
	return it-1;
}

int at(node* map, int n, int src){
	for(int i = 0; i<n;i++){
		if(src >= map[i].src && src <= (map[i].src+map[i].range-1)){
			unsigned offset = src - map[i].src;
			return map[i].dest + offset;
		}
	}
	return src;
}

node* at_node(node* map, int* p_n, int src){
	int n = *p_n;
	for(int i = 0; i<n;i++){
		if(src >= map[i].src && src <= (map[i].src+map[i].range-1)){
			return map+i;
		}
	}
	unsigned nearer_src = UINT_MAX;
	for(int i = 1; i<n;i++){
		if(map[i].src > src && map[i].src < nearer_src){
			nearer_src = map[i].src;
		}
	}
	map[n].src = src;
	map[n].dest = src;
	map[n].range = nearer_src - src;
	printf(" new node added: src: %u dest: %u range: %u\n",  map[n].src, map[n].dest, map[n].range);

	(*p_n)++;
	return map+n;
}

int update_seed_map(node* seed_map, int nb_seed, node* map, int* p_map_len){
	int map_len = *p_map_len;
	int original_nb_seed = nb_seed;
	printf("\ndealing with seed_map:\n");
	for(int i = 0; i < original_nb_seed; i++){
		/*
			   src range
		plage:   5  4     (5 -  8) <=> (5 - 6) + (7 - 8)

			   src des range
		mapping: 4   0  3  (4 -  6 -->  0 -  2)
				 7  10  4  (7 - 10 --> 10 - 13)

		res: 	 5  4 -->   0  2  ( 1 -  2)
						   10  2  (10 - 11)
		*/
		printf("step: nb_seed = %d; i = %d\n", nb_seed, i);

		unsigned seed_src = seed_map[i].src;       //  5 
		unsigned seed_range = seed_map[i].range;   //  4
		printf(" seed src %u\n", seed_src);


		node* n = at_node(map, p_map_len, seed_src);  // node: 4  0  3
		printf(" node: src: %u dest: %u range: %u\n",  n->src, n->dest, n->range);

		unsigned offset = seed_src - n->src;        // 5 - 4 = 1
		unsigned free_space = n->range - offset;    // 3 - 1 = 2

		unsigned future_seed_src = n->dest + offset; // 0 + 1 = 1    // equ to f_src = at(map, map_len, src);
		unsigned future_seed_range = seed_range;              // 4 but could be modified because 4 > 2 (free_space)

		seed_map[i].src = future_seed_src;
		seed_map[i].range = future_seed_range;
		while(free_space < future_seed_range){
			printf(" must split range, free_space: %u range %u\n", free_space, future_seed_range);
			future_seed_range = free_space; // 2
			seed_map[i].range = future_seed_range;
			// create another node starting at: seed_src + free_space - 1 of range to be determinated
			seed_src += free_space;         // 5 + 2 = 7
			seed_range -= free_space;       // 4 - 2 = 2
			printf(" new seed src %u\n", seed_src);
			n = at_node(map, p_map_len, seed_src); // node: 7  10  4
			printf(" node: src: %u dest: %u range: %u\n", n->src, n->dest, n->range);
			offset = seed_src - n->src;          // 7 - 7 = 0
			free_space = n->range - offset;      // 3 - 0 = 3
			printf(" seed offset %u\n", offset);

			future_seed_src = n->dest + offset; // 7 + 0 = 7
			printf(" seed future src %u\n", future_seed_src);

			future_seed_range = seed_range;              // 2    // will not be modified because 2<3

			seed_map[nb_seed].src = future_seed_src;
			seed_map[nb_seed].range = future_seed_range;
			nb_seed++;
		}
	}
	return nb_seed;
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	input_file = fopen(filename, "r");
	size_t tot = 0;

	size_t MAX_SEEDS = 200;
	int nb_seed = 0;
	node* seed_map = malloc(sizeof(node*)*MAX_SEEDS);

	fscanf(input_file, "seeds:");

	int err = 0;
	do{
		err = fscanf(input_file, "%d %d", &seed_map[nb_seed].src, &seed_map[nb_seed].range);
		//printf("err: %d; seed: %d\n", err, seeds[seed]);
		seed_map[nb_seed].dest = -1;
		nb_seed++;
	}while(err);
	nb_seed--;
	printf("last seed is: %u\n", seed_map[nb_seed-1].src);

	fscanf(input_file, "seed-to-soil map:");
	node* map = malloc(sizeof(node)*100);
	int map_len = read_map(map);

	// printf("\nseed map before: \n");
	// for(int i = 0; i < nb_seed; i++)
	// 	printf(" src %d range %d \n", seed_map[i].src, seed_map[i].range);

	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);
	
	// printf("\nseed map after: \n");
	// for(int i = 0; i < nb_seed; i++)
	// 	printf(" src %d range %d \n", seed_map[i].src, seed_map[i].range);

	fscanf(input_file, "soil-to-fertilizer map:");
	map_len = read_map(map);
	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);

	fscanf(input_file, "fertilizer-to-water map:");
	map_len = read_map(map);
	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);

	fscanf(input_file, "water-to-light map:");
	map_len = read_map(map);
	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);

	fscanf(input_file, "light-to-temperature map:");
	map_len = read_map(map);
	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);

	fscanf(input_file, "temperature-to-humidity map:");
	map_len = read_map(map);
	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);

	fscanf(input_file, "humidity-to-location map:");
	map_len = read_map(map);
	nb_seed = update_seed_map(seed_map, nb_seed, map, &map_len);

	node* nearer_node = seed_map;
	for(int i = 1; i<nb_seed;i++){
		if(seed_map[i].src < nearer_node->src){
			nearer_node = seed_map+i;
			printf("found a smaller location: %d\n", seed_map[i].src);
		}
	}
	tot = nearer_node->src;

	printf("%d\n", tot);
	return 0;
}
