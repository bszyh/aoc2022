#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 1024
#define ITEM_SIZE 3000 
#define SHARED 1000

// second part of the puzzle

int main() {
	
	FILE *fp;
	char buffer[BUFF_SIZE];

	int rucksack_s = 0; // size of the rucksack
	char shared_items[SHARED]; // stores repeated items 
	int r = 0; // counter for shared items array
	int line_c = 0;
	int group_c = 0;

	// check before opening the txt file 
	if(fopen("input.txt", "r") == NULL) {
		printf("error! cannot open the file :-(");
	} else {
		fp = fopen("input.txt", "r");
	}

	int letters[ITEM_SIZE] = {0}; //switch form bool for the second part of the puzzle, cuz we counting to 3 now 
	
	//this is the change part for the second part of the puzzle
	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {

		rucksack_s = strlen(buffer) - 1; //size minus the new line char at the end "\n"
		
		if(group_c == 3) {
			group_c = 1;
			printf("another group!\n");
			for(int i = 0; i < ITEM_SIZE; i++) { letters[i] = 0; }
		} else {
			group_c++;
		}

		//fuck compartments
		printf("buffer: %s\n", buffer);

		switch(group_c) {
			case 1:
				for(int i = 0; i < rucksack_s; i++) {
					int c = (int)(buffer[i]);
					if(letters[c] == 0) { letters[c] = 1; }
				}
				break;
			case 2:
				for(int i = 0; i < rucksack_s; i++) {
					int c = (int)(buffer[i]);
					if(letters[c] == 1) { letters[c] = 2; }
				}
				break;
			case 3:
				for(int j = 0; j <= rucksack_s; j++) {
					int c = (buffer[j]);
					if(letters[c] == 2) {
						shared_items[r] = buffer[j];
						r++;
						break; // this solves the "letters repeating "within" the compartment :-)
					}
				}
				line_c++;
				break;
		}
	}
	
	int total_score = 0;

	for(int i = 0; i < line_c; i++) {
		printf("badge for %dth group: %c\n", i, shared_items[i]);
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
