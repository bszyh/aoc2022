#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIR 100000
#define BUFF_SIZE 1000

typedef struct Dir {
	char *name;
	int size;
	struct Dir *parent;
	struct Dir **children;
} Dir;

//for now as global so they are available for functions without passing them in

	Dir *cwd = NULL;
	Dir root = {"/", 0, NULL, NULL};

int addDir(Dir *parent, Dir *child) {
	if(parent == NULL) return 1;
	if(child == NULL) return 2;

	size_t ndir = 0;

	if(parent->children != NULL) {
		while(parent->children[ndir] != NULL) {
			ndir++;
		}
	}

	Dir *new_dir = realloc(parent->children, (ndir + 2) * sizeof(Dir*));
	if(new_dir == NULL) return 3;

	parent->children = (Dir**)new_dir;
	parent->children[ndir++] = child; //sets child at parent-children[ndir] and then increments the ndir variable
	parent->children[ndir] = NULL; //end of the array
	
	child->parent = parent;

	return 0;
}

void printBelow(Dir *parent) {
	if(parent != NULL) {
		size_t ndir = 0;

		if(parent->children != NULL) {
			while(parent->children[ndir] != NULL) {
				printf("dir name: %s\n", parent->children[ndir]->name);
				ndir++;
			}
		}
	}
}

int printCurrentDir(char *buffer, int buff_length) {
	if( buffer[5] == '.') { return 0;}

	printf("current working directory: ");
	// i = 5 because form this point the name tag starts	
	for(int i = 5; i < buff_length; i++) {
		printf("%c", buffer[i]);
	}
	printf("\n");
	return 1;
}

int cd_command(char *buffer, int buff_len) {
	// "$ cd " - 4 first chars are not needed here tbh, so we start from 5 index	
	
	if(buffer[5] == '.' && buffer[6] == '.') { // case for "$ cd .."
		//change current working directory to parent node (directory that contains cwd)
		cwd = cwd->parent; //not sure about this one - check
	} else if(buffer[5] == '/') {
		cwd = &root;
		//change current working directory to root
	} else {
		// change current working directory to name directory contained in the cwd
		// so loop through children and find the dir "name"
		char *name;
		int c = 5, i = 0;
		
		// here the copy might be confusing but i need to handle both the new line char and null termination in buffer
		while((name[i] = buffer[c]) != '\n') {
			c++;
			i++;
		}

		//now add the null termination
		name[++c] = '\0';

		size_t ndir = 0;
		Dir *tmp = NULL;
		if(cwd->children != NULL) {
			while(cwd->children[ndir] != NULL) {
				//here gotta use strcmp
				if(strcmp(cwd->children[ndir]->name, name) == 0) {
					tmp = cwd->children[ndir];
					break;
				}
				ndir++;
			}
		}

		cwd = tmp;

	}
		

	return 0;
}

int ls_command(char *buffer, int buff_len) {
	// here i handle the addition of the nodes to the tree so thread carefully
	
	// if line starts with 'dir' so char d - add the node as a child to the cwd (parent)
	if(buffer[0] == 'd') {
		
		char *name;
		int c = 5, i = 0;
		
		// here the copy might be confusing but i need to handle both the new line char and null termination in buffer
		while((name[i] = buffer[c]) != '\n') {
			c++;
			i++;
		}

		//now add the null termination
		name[++c] = '\0';

		//create new node
		Dir node = {name, 0, cwd, NULL};

		//add node as child to cwd
		addDir(cwd, &node);
	}
	return 0;
}

void commandHandler(char *buffer, int buff_length) {
	for(int i = 0; i < buff_length; i++) {

		
	}
}


int main(void) {
	
	FILE *fp;
        char buffer[BUFF_SIZE];

	if(fopen("input.txt", "r") == NULL) {
		perror("can't open the file");
	} else {
		fp = fopen("input.txt", "r");
	}

	// now the main thing is to either make a buffer for handling the ls command or allow conditon on which the line gets incremented
	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {

		//printf("%s\n", buffer);
		// something to think about, is to use switch to check for buffer[2] either for ls or cd, the dir is going to be processed inside ls command anyway
		if(buffer[0] == '$') {
			switch(buffer[2]) {
				case 'l': //here we get straight to the next line for processing
					while(fgets(buffer, BUFF_SIZE, fp) != NULL) {
						if(buffer[0] == '$') { break; }
						printf("inside the ls command set!\n");
						ls_command(buffer, strlen(buffer));
					}
				case 'c':
					printf("cd: %s\n", buffer);
					printCurrentDir(buffer, strlen(buffer));
					cd_command(buffer, strlen(buffer));
					//printf("command: %s\n", buffer);
				break;
			}
		}
	}

	fclose(fp);

	return 0;
}
