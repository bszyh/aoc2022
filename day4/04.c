#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 25

struct number {
	int digit1;
	int digit2;
	int num1;
	int num2;
};

struct pair {
	struct number elf1;
	struct number elf2;
	int elf_flag;
};

int check_range(struct pair elfs) {
	
	int x1 = elfs.elf1.num1;
	int x2 = elfs.elf2.num1;
	int y1 = elfs.elf1.num2;
	int y2 = elfs.elf2.num2; 

	//for ranges containing each other entirely
	if((x1 <= x2) && (y1 >= y2)) { // the first range contains the second one
		return 1;	
	} else if((x2 <= x1) && (y2 >= y1)) { // the second range contains the first one
		return 1;
	} 

	//for overlapping ranges
	if((x1 <= x2) && (y1 >= x2)) {
		return 2;
	} else if((x1 >= x2) && (x1 <= y2)) {
		return 2;
	}
	return 0;
}


int main(void) {

	FILE *fp;
	char buffer[BUFF_SIZE];

	if(fopen("input.txt", "r") == NULL) {
		printf("sorry, problem with opening the input file\n");
	} else {
		fp = fopen("input.txt", "r");
	}
	
	int line_c = 0, contained_pairs = 0, overlapping_pairs = 0;

	struct pair E;
	E.elf_flag = 0;

	struct number N;
	N.digit1 = 100;
	N.digit2 = 100;

	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {
		
		for(int i = 0; i < strlen(buffer); i++) {
			switch(buffer[i]) {
				case '-': // range
					if(N.digit2 != 100) {
						N.num1 = N.digit1 * 10 + N.digit2;
					} else {
						N.num1 = N.digit1;
					}
					if(E.elf_flag == 0) { 
						E.elf1.num1 = N.num1;
						E.elf_flag = 1;
						printf("the first elf - num1: %d\n", E.elf1.num1);
					} else {
						//here for elf2
						E.elf2.num1 = N.num1;
						printf("the second elf - num1: %d\n", E.elf2.num1);
					}
					N.digit1 = 100;
					break;
				case ',': // other elf in the pair
					if(N.digit2 != 100) {
						N.num2 = N.digit1* 10 + N.digit2;
					} else {
						N.num2 = N.digit1;
					}
					E.elf1.num2 = N.num2;
					printf("the first elf - num2: %d\n", E.elf1.num2);
					N.digit1 = 100;
					break;
				case '\n': // next pair
					if(N.digit2 != 100) {
						N.num2 = N.digit1* 10 + N.digit2;
					} else {
						N.num2 = N.digit1;
					}
					E.elf2.num2 = N.num2;
					printf("the second elf - num2: %d\n", E.elf2.num2);
					printf("next pair\n");
					if(check_range(E) == 1) {
						contained_pairs++;
						overlapping_pairs++;
					} else if(check_range(E) == 2) {
						overlapping_pairs++;
					}
					N.digit1 = 100;
					E.elf_flag = 0;
					break;
				default: // the numbers

					if(N.digit1 == 100) {
						N.digit1 = (int)(buffer[i] - '0');
						N.digit2 = 100;
					} else {
						N.digit2 = (int)(buffer[i] - '0');
					}
			}
		}
		line_c++;
	}
	
	printf("overlapping pairs: %d\n", overlapping_pairs);
	printf("pairs that contain each others full range: %d\n", contained_pairs); // ok so thats fucken wrong ig
	printf("total line count: %d\n", line_c);

	fclose(fp);

	return 0;
}
