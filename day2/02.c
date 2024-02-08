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

// X - lose, Y - draw, Z -win

enum Score { draw=3, win=6 };

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

	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {

		//printf("buffer[0]: %c, buffer[2]: %c\n", buffer[0], buffer[2]);

		// elf
		if(buffer[0] == 65) {
			elf_m = 1;
		}
		if(buffer[0] == 66) {
			elf_m = 2;
		}
		if(buffer[0] == 67) {
			elf_m = 3;
		}

		// player (actually the result)
		if(buffer[2] == 88) {
			player_m = 1;
		}
		if(buffer[2] == 89) {
			player_m = 2;
		}
		if(buffer[2] == 90) {
			player_m = 3;
		}


		int tmp = elf_m * player_m;
		int player_bigger = (player_m > elf_m) ? 1 : 0;

		switch(tmp) {
			case 2:
				if(player_bigger) { points += player_m + win; }
     				else { points += player_m; }
				break;
			case 3:
				if(player_bigger) { points += player_m; }
				else { points += player_m + win; }
				break;
			case 6:
				if(player_bigger) { points += player_m + win; }
				else { points += player_m; }
				break;
			default:
				points += player_m + draw;
		}
	}

	printf("total points: %d\n", points);

	return 0;
}
