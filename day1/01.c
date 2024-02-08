#include <stdio.h>
#include <string.h>

//now gotta change it to top three elves with most kcals :P

struct elves {
	int top1;
	int top2;
	int top3;
};

void check_calories(struct elves *most_kcal, int kcal) {

	//here at first i forgot when the top 3 and 2 changes to push the old value to the next lesser top!
	if(kcal > most_kcal->top1) {
		most_kcal->top3 = most_kcal->top2;
		most_kcal->top2 = most_kcal->top1;
		most_kcal->top1 = kcal;
	} else if (kcal > most_kcal->top2) {
		most_kcal->top3 = most_kcal->top2;
		most_kcal->top2 = kcal;
	} else if (kcal > most_kcal->top3) {
		most_kcal->top3 = kcal;
	}
}

int main(void) {

	FILE *fp;
	char buffer[124];
	int calories_max = 0, elf_kcal = 0, elf_count = 0;

	struct elves most_kcal;

	most_kcal.top1 = 0;
	most_kcal.top2 = 0;
	most_kcal.top3 = 0;
	
	if(fopen("input.txt","r") == NULL) {
		printf("Error, cannot open this file");
	} else {
		fp = fopen("input.txt","r");;
	}
		
	while(fgets(buffer, sizeof buffer, fp) != NULL) {
		if(strcmp(buffer,"\n") == 0) { //strcmp returns 0 if the strings are equal (RTFM!)
			check_calories(&most_kcal, elf_kcal);
			elf_count++;
			elf_kcal = 0;
		} else {
			int kcal;
			sscanf(buffer, "%d", &kcal);

			elf_kcal += kcal;
			if(elf_kcal > calories_max) { calories_max = elf_kcal; }
		}

	}

	printf("biggest amount of total kcal (%d) is carried by the %dth elf!\n", calories_max, elf_count);
	printf("total amount of kcals carried by the top 3 elves with most kcal: %d\n", top3_kcal);

	fclose(fp);

	return 0;	

}
