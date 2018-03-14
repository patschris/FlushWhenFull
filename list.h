#ifndef _list_
#define _list_

typedef struct Node {
	char* address;		// memory address
	char status;		// Read/Write (R/W)
	int pid;			// Process IDentifier
	struct Node *next;
}Node;

typedef struct List {
	Node *first;		// first node
	int size;			//size of the list
}List;

List* createList(void);
void insert(List*, char *, char, int);
void printList(List*);
void deleteFirstNode(List*);
void destroyList(List*);
Node *createNode (char *, char, int);
void clearNode (Node *);
void setNode (Node *, char *, char, int);

#endif