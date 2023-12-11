#!/usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* FILENAME = "input.txt";

unsigned long compute_nb_of_possibility(unsigned long* times, unsigned long* distances, int n){
	unsigned long tot = 1;
	for(int i = 0; i < n; i++){
		int nb_poss = 0;
		for(unsigned long j = 0; j<=times[i]; j++){
			if(j*(times[i]-j) > distances[i])
				nb_poss++;
		}
		tot*=nb_poss;
	}
	return tot;
}

int main(int argc, char** argv){
	char* filename = FILENAME;
	if (argc > 1) {
		filename = argv[1];
	}
	FILE* input_file = fopen(filename, "r");

	int n = 0;
	unsigned long times[10];
	unsigned long distances[10];

	fscanf(input_file, "Time:");
	int err = 0;
	do{
		err = fscanf(input_file, "%lu", times+n);
		//printf("err: %d; seed: %d\n", err, seeds[seed]);
		n++;
	}while(err);
	n--;

	fscanf(input_file, "Distance:");
	for(int i = 0; i < n; i++)
		fscanf(input_file, "%lu", distances+i);

	fclose(input_file);

	input_file = fopen(filename, "r");
	fscanf(input_file, "Time:");
	char buf[100];
	char stime[100];
	int i = 0;
	fgets(buf, 100, input_file);
	char* p = buf;
	while(*p){
		if(isdigit(*p)){
			stime[i] = *p;
			i++;
		}
		p++;
	}
	unsigned long time = strtoul(stime, &p, 10);
	
	fscanf(input_file, "Distance:");
	fgets(buf, 100, input_file);
	p = buf;
	printf("buf: %s\n", buf);
	i=0;
	char sdistance[100];
	while(*p){
		if(isdigit(*p)){
			sdistance[i] = *p;
			i++;
		}
		p++;
	}
	unsigned long distance = strtoul(sdistance, &p, 10);
	printf("time: %lu, distance: %lu\n", time, distance);

	printf("part1: %lu\n", compute_nb_of_possibility(times,distances, n));
	printf("part2: %lu\n", compute_nb_of_possibility(&time,&distance, 1));
	fclose(input_file);
	return 0;
}
