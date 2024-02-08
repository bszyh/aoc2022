#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char data;
	struct Node *parent;
	struct Node **children; // this is supposed to be a ptr to an array of children 
} Node;


int addChild(Node *parent, Node *child) {
	if(parent == NULL) { return 1; }
	if(child == NULL) { return 2; }

	size_t nchild = 0;
	if(parent->children != NULL) {
		while(parent->children[nchild] != NULL) {
			nchild++;
		}
	}

	Node *new_child = realloc(parent->children, (nchild + 2) * sizeof(Node*));
	if(new_child == NULL) { return 3; }
	
	parent->children = (Node**)new_child; //cast to Node**, othervise warning and then realloc gets fucked up on second call to function
	parent->children[nchild++] = child; // add child to the parent
	parent->children[nchild] = NULL; // signifies the end of the array - after the new child

	child->parent = parent;	
	return 0;
}

void printChildren(Node *parent) {
	if(parent != NULL) { 
			
		size_t nchild = 0;
		if(parent->children != NULL) {
			while(parent->children[nchild] != NULL) {
				printf("child: %c\n", parent->children[nchild]->data);
				nchild++;
			}
		}
	}
}

int main(void) {
	
	Node n1= { 'A', NULL, NULL};
	Node n2 = { 'B', NULL, NULL};
	Node n3 = { 'C', NULL, NULL};
	Node n4 = { 'D', NULL, NULL};
	Node n5 = { 'E', NULL, NULL};
	Node n6 = { 'F', NULL, NULL};

	printf("%d\n", addChild(&n1, &n2));
	printf("%d\n", addChild(&n1, &n3));

	printf("%d\n", addChild(&n2, &n4));
	printf("%d\n", addChild(&n2, &n5));
	
	printf("%d\n", addChild(&n4, &n6));

	printChildren(&n1);
	printChildren(&n2);
	printChildren(&n4);

	return 0;
}
