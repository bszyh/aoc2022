#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFF_S 5000
#define M_LENGTH 14

typedef struct Node {
	char data;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *front; // after this one we enqueue
	Node *rear; // the next to dequeue
} Queue;

void enQueue(Queue *kolejka, char value) {
	Node *newnode = (Node*)malloc(sizeof(Node)); //create new node
	if (newnode == NULL) { printf("memory allocation failed!\n"); }

	newnode->data = value; // assign the new value to the node
	newnode->next = NULL; // because its now the rear
	
	if( kolejka->front == NULL) {	
		// queue empty
		kolejka->front = newnode;
		kolejka->rear = newnode;
	} else {
		// queue not empty
		kolejka->rear->next = newnode;
		kolejka->rear = newnode;
	}
}

void deQueue(Queue *kolejka) {
	if(kolejka->front == NULL) { printf("queue empty!\n"); }
	else {
		Node *tmp = kolejka->front; //store previous front
		kolejka->front = kolejka->front->next; // move front one node ahead

		if(kolejka->front == NULL) {
			kolejka->rear = NULL;
		}

		free(tmp);
	}
}

void printQueue(Queue *kolejka) {
	if(kolejka->front == NULL) { printf("queue empty, can't print!\n"); }
	else {
		Node *tmp = kolejka->front;
		do {
			printf("%c", tmp->data);
		} while((tmp = tmp->next) != NULL);
	}
	printf("\n");
}

int sizeQueue(Queue *kolejka) {

	if(kolejka->front == NULL) { return 0; }

	int size = 0; 
	Node *tmp = kolejka->front;

	while(tmp != NULL) {
		size++;
		tmp = tmp->next;
	}

	return size;
}

int check(Queue *kolejka) {

	int size = sizeQueue(kolejka);
	//printf("size: %d\n", size);

	if(size > M_LENGTH) { // more than 4 items in queue
		deQueue(kolejka);
		size = sizeQueue(kolejka);
	} 

	if(size < M_LENGTH) { // less than 4 items in queue
		// printf("kolejka less than 4\n");
		return 0;
	}

	if(size == M_LENGTH) {
	// default operations
		printf("kolejka state check: ");
		printQueue(kolejka);

		char array[M_LENGTH];
		int c = 0;
		Node *tmp = kolejka->front; // the first item in the queue
		while(tmp != NULL) {
			array[c] = tmp->data;
			c++;
			tmp = tmp->next;
		}

		for(int i = 0; i < M_LENGTH - 1; i++) {
			for(int j = i + 1; j < M_LENGTH; j++) {
				if(array[i] == array[j]) {
					return 0;
				}
			}
		}
		return 1;	
	}

}


int main(void) {
	
	FILE *fp;
	char buffer[BUFF_S];

	if(fopen("input.txt", "r") == NULL) {
		printf("can't open the file :-(\n");
	} else {
		fp = fopen("input.txt", "r");
	}

	Queue *kolejka= (Queue*)malloc(sizeof(Queue));
	kolejka->front = kolejka->rear = NULL;

	
	int item = 0;
	int result = 0;

	fgets(buffer, BUFF_S, fp); // store the stream in the buffer
	
	for(int i = 0; i < strlen(buffer); i++) {
		if(result == 1) {
			printf("MARKER!\n");
			break;
		}
		enQueue(kolejka, buffer[i]);
		result = check(kolejka);
		item++;
	}

	printf("marker + items: %d\n", item);

	free(kolejka);

	fclose(fp);

	return 0;
}
