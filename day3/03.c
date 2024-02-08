#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 1024
#define ITEM_SIZE 3000 
#define SHARED 1000


int main() {
	
	FILE *fp;
	char buffer[BUFF_SIZE];

	int rucksack_s = 0; // size of the rucksack
	int compartment_s = 0; // size of the compartment
	char shared_items[SHARED]; // stores repeated items 
	int r = 0; // counter for shared items array
	int line_c = 0;

	// check before opening the txt file 
	if(fopen("input.txt", "r") == NULL) {
		printf("error! cannot open the file :-(");
	} else {
		fp = fopen("input.txt", "r");
	}


	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {
		rucksack_s = strlen(buffer) - 1; //size minus the new line char at the end "\n"
		compartment_s = rucksack_s / 2;	
		bool letters[ITEM_SIZE] = {false};

		//for first compartment
		for(int i = 0; i < compartment_s; i++) {
			int c = (int)(buffer[i]);
			if(letters[c] == false) {
				letters[c] = true;
			}
		}

		//second compartment
		for(int j = compartment_s; j <= rucksack_s; j++) {
			int c = (buffer[j]);
			if(letters[c] == true) {
				shared_items[r] = buffer[j];
				r++;
				break; // this solves the "letters repeating "within" the compartment :-)
			}
		}
		line_c++;
	}
	
	int total_score = 0;

	for(int i = 0; i < line_c; i++) {
		printf("repeated item in %dth rucksack: %c\n", i + 1, shared_items[i]);
		if(shared_items[i] < 97) {
			total_score += (int)shared_items[i] - 38;
		} else {
			total_score += (int)shared_items[i] - 96;
		}
	}

	printf("sum of the priorities for the shared items: %d\n", total_score);

	fclose(fp);


	return 0;
}
