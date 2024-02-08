#include <stdio.h>
#include <stdlib.h> //for memory allocation - malloc
#include <stdbool.h>
#include <string.h>

// void *malloc(size_t size); -> takes "size" of bytes to allocate, if sucessfull returns ptr to that memory, otherwise returns NULL

// HEAD -> ptr to the TOP of the stack

typedef struct Node {
	char data; // value
	struct Node *next; // ptr to the next node, needs the struct keyword cuz comes before naming with typedef
} Node;

typedef Node *Stack; // from now on "Stack" means a pointer to struct type Node

bool push(Stack *mystack, char value) { // here "mystack" is a pointer to a pointer, basically it stores the address of a pointer to the struct Node type
					// which is why we must use the "*" before each mystack, to get to the Stack pointer (Node*)
	Node *newnode = (Node*)malloc(sizeof(Node));

	if(newnode == NULL) { return false; } // if the memory allocation didn't succeed
	
	newnode->data = value;
	newnode->next = *mystack; // *mystack instead of global head, because it could be a different stack
	
	*mystack = newnode; // here we make the newnode a current "head" of the stack
	return true;
}

char pop(Stack *mystack) {
	if(*mystack == NULL) { 
		printf("POP NULL ALLERT!");
		return '\0'; 
	} // if stack is empty we have nothing to pop from it
	else {	
		char result = (*mystack)->data;
		Node *tmp = *mystack;
		*mystack = (*mystack)->next;
		free(tmp);
		return result;
	}
}

// second part of the puzzle: moving multiple items at a time in a way that they retain their order

bool moveItem(Stack *popstack, Stack *pushstack, int items) {
	
	if(*popstack == NULL) { return false; }
	
	//need a dynamically allocated array, cuz the size for static one needs to be known at compile time, not runtime
	char *order = (char*)malloc(items * sizeof(char));
	if(order == NULL) { return false; } // memory allocation failed

	for(int i = 0; i < items; i++) {
		char tmp = pop(popstack);
		if(tmp == '\0') { return false; }
		order[i] = tmp;
	}

	for(int i = items - 1; i >= 0 ; i--) {
		push(pushstack, order[i]);
	}
	
	free(order);
	// old part
	/*for(int i = 0; i < items; i++) {
		char tmp = pop(popstack); 
		if(tmp == '\0') { return false; }
		push(pushstack, tmp);
	}*/

	return true;
}

void fillStack(char crates[], int arr_l, Stack *stack) {

	for(int i = 0; i < arr_l; i++) {
		if(push(stack, crates[i]) == false) { break; }
	}
}

char getHeadData(Stack *s) {
	if(*s != NULL) {	
		return (*s)->data;
	} else { return '\0'; }
}

// now to figure other needed options for the stack to be usable, also the operations to move items between stacks

#define BUFF_SIZE 500

int main(void) {
	
	// think if i could make an array of stacks?
	Stack s1 = NULL, s2 = NULL, s3 = NULL, s4 = NULL, s5 = NULL, s6 = NULL, s7 = NULL, s8 = NULL, s9 = NULL;
	Stack *all_stacks[9] = {&s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9};	

	// fill the stacks
	char c1[5] = {'R', 'S', 'L', 'F', 'Q'};		
	char c2[6] = {'N', 'Z', 'Q', 'G', 'P', 'T'};		
	char c3[4] = {'S', 'M', 'Q', 'B'}; 
	char c4[8] = {'T', 'G', 'Z', 'J', 'H', 'C', 'B', 'Q'};		
	char c5[7] = {'P', 'H', 'M', 'B', 'N', 'F', 'S'}; 	
	char c6[8] = {'P', 'C', 'Q', 'N', 'S', 'L', 'V', 'G'};
	char c7[3] = {'W', 'C', 'F'};
	char c8[8] = {'Q', 'H', 'G', 'Z', 'W', 'V', 'P', 'M'};
	char c9[7] = {'G', 'Z', 'D', 'L', 'C', 'N', 'R'}; 	
	
	fillStack(c1, (int)sizeof(c1), &s1);
	fillStack(c2, (int)sizeof(c2), &s2);
	fillStack(c3, (int)sizeof(c3), &s3);
	fillStack(c4, (int)sizeof(c4), &s4);
	fillStack(c5, (int)sizeof(c5), &s5);
	fillStack(c6, (int)sizeof(c6), &s6);
	fillStack(c7, (int)sizeof(c7), &s7);
	fillStack(c8, (int)sizeof(c8), &s8);
	fillStack(c9, (int)sizeof(c9), &s9);
	

	// now read the instructions
	FILE *fp;
	char buffer[BUFF_SIZE];

	if(fopen("input.txt", "r") == NULL) {
		printf("unable to open the requested file!\n");
	} else {
		fp = fopen("input.txt", "r");
	}

	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {
		int move[3];
		int c = 0;
		
		//someone forgor that the move integers can be double digits u dingus
		for(int i = 0; i < strlen(buffer); i++) {
			if(((int)buffer[i] > 48) && ((int)buffer[i] < 58)) {
				int val;
				if(((int)buffer[i + 1] > 47) && ((int)buffer[i + 1] < 58)) {
					val = (buffer[i] - '0') * 10 + (buffer[i + 1] - '0');
					i++;
				} else { 
					val = buffer[i] - '0'; 
				}

				move[c] = val; 
				c++;
			}
		}

		int item_amount = move[0];
		int stackid_from = move[1] - 1;
		int stackid_to = move[2] - 1;
		bool result = moveItem(all_stacks[stackid_from], all_stacks[stackid_to], item_amount);
		if(result != true) { printf("moveItem didn't work :-(\n"); }
	}
	
	printf("Crates on top: ");	
	for(int i = 0; i < 9; i++) {
		Stack **tmp = &(all_stacks[i]);
		printf("%c", getHeadData(*tmp));
	}	
	

	printf("\n");
	fclose(fp);

	return 0;
}
