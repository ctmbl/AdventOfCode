//#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	input_file = fopen(filename, "r");
	size_t tot = 0;

	size_t MAX_SEEDS = 100;
	int seed = 0;
	int* seeds = malloc(sizeof(int)*MAX_SEEDS);

	char str[64] = {0};
	int a = 0;
	
	fscanf(input_file, "seeds:");

	int err = 0;
	do{
		err = fscanf(input_file, "%d", seeds+seed);
		//printf("err: %d; seed: %d\n", err, seeds[seed]);
		seed++;
	}while(err);
	seed--;
	printf("last seed is: %u\n", seeds[seed-1]);

	fscanf(input_file, "seed-to-soil map:");
	node* seed_to_soil = malloc(sizeof(node)*100);
	int sts = read_map(seed_to_soil);

	fscanf(input_file, "soil-to-fertilizer map:");
	node* soil_to_fertilizer = malloc(sizeof(node)*100);
	int stf = read_map(soil_to_fertilizer);

	fscanf(input_file, "fertilizer-to-water map:");
	node* fertilizer_to_water = malloc(sizeof(node)*100);
	int ftw = read_map(fertilizer_to_water);

	fscanf(input_file, "water-to-light map:");
	node* water_to_light = malloc(sizeof(node)*100);
	int wtl = read_map(water_to_light);

	fscanf(input_file, "light-to-temperature map:");
	node* light_to_temperature = malloc(sizeof(node)*100);
	int ltt = read_map(light_to_temperature);

	fscanf(input_file, "temperature-to-humidity map:");
	node* temperature_to_humidity = malloc(sizeof(node)*100);
	int tth = read_map(temperature_to_humidity);

	fscanf(input_file, "humidity-to-location map:");
	node* humidity_to_location = malloc(sizeof(node)*100);
	int htl = read_map(humidity_to_location);
	
	printf("last range of last map %d\n", humidity_to_location[htl-1].range);

	unsigned min_loc = -1;
	for(int i = 0; i<seed;i++){
		int loc = at(humidity_to_location,htl,at(temperature_to_humidity, tth,at(light_to_temperature, ltt,at(water_to_light, wtl,at(fertilizer_to_water, ftw,at(soil_to_fertilizer, stf, at(seed_to_soil, sts, seeds[i])))))));
		if(loc < min_loc)
			min_loc = loc;
	}
	tot = min_loc;

	printf("%d\n", tot);
	fclose(input_file);
	return 0;
}
