#include <stdio.h>
#include <string.h>
// rock paper scisors

/* the question is now on how to implement the logic of rock paper scissors
 * cases: paper - beats rock (2 * 1) 2
 * 	  rock - beats scissor (1 * 3) 3
 * 	  scissors - beat paper (3 * 2) 6
 * 	  othervise draw
 * 	  -> using multiplication
 * 	  we are intrested only in the score of the player
 */

#define BUFFER_SIZE 50

// rock - 1, paper - 2, scissors - 3
// X - lose, Y - draw, Z -win -> second part of the puzzle

int main(void) {

	FILE *fp;
	char buffer[BUFFER_SIZE];

	if(fopen("input.txt", "r") == NULL) {
		printf("sorry, couldn't open the file!\n");
	} else {
		fp = fopen("input.txt", "r");
	}


	int points = 0;
	int elf_m = 0;
	int player_m = 0;
	int result = 0;
	
	// second part of the puzzle
	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {

		//printf("buffer[0]: %c, buffer[2]: %c\n", buffer[0], buffer[2]);

		switch(buffer[0]) {
			case 'A':
				elf_m = 1;
				if(buffer[2] == 'Z') {
					//player win
					player_m = 2;
					result = 6;
				} else if(buffer[2] == 'X') {
					//player lose
					player_m = 3;
					result = 0;
				}
				break;
			case 'B':
				elf_m = 2;
				if(buffer[2] == 'Z') {
					//player win
					player_m = 3;
					result = 6;
				} else if(buffer[2] == 'X') {
					//player lose
					player_m = 1;
					result = 0;
				}
				break;
			case 'C':
				elf_m = 3;
				if(buffer[2] == 'Z') {
					//player win
					player_m = 1;
					result = 6;
				} else if(buffer[2] == 'X') {
					//player lose
					player_m = 2;
					result = 0;
				}
				break;
		}

		if(buffer[2] == 'Y') { //draw
			player_m = elf_m;
			result = 3;
		}
		
		points += (player_m + result);
	}
	
	printf("Total player points for the second part of the puzzle: %d\n", points);
	
	fclose(fp);

	return 0;
}
