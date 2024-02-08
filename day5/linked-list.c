#include <stdio.h>
#include <stdlib.h> //for memory allocation - malloc
#include <stdbool.h>

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
	if(*mystack == NULL) { return '\0'; } // if stack is empty we have nothing to pop from it
	
	char result = (*mystack)->data;
	Node *tmp = *mystack;
	*mystack = (*mystack)->next;
	free(tmp);
	
	return result;
}


int main(void) {
	
	Stack s1 = NULL, s2 = NULL, s3 = NULL;
	char alpha = 'A' - 1;
	for(int i = 65; i <= 90; i++) {
		alpha++;
		//printf("%c\n", alpha);
		push(&s1, alpha);
	}
	
	char beta;
	while((beta = pop(&s1)) != '\0') {
		printf("%c\n", beta);
	}

	return 0;
}
