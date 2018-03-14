#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* 
 * Allocate and initialize a new list 
 */
List* createList(void) {
	List* l;
	if ((l = (List*) malloc(sizeof (List))) == NULL) {
		perror("List's allocation failed");
		exit(-1);
	} 
	l->size = 0;
	l->first = NULL;
	return l;
}

/* 
 * Allocate and add a new node as the first node of an existing list l 
 * Node is initialized using function's arguments
 */
void insert(List* l, char *addr, char stat, int id) {
	Node *n = createNode(addr, stat, id);
	Node *temp = l->first;
	l->first = n;	
	n->next = temp;
	l->size++;
}

/*
 * Print the contents of an existing list l
 */
void printList(List* l) {
	Node* temp = l->first;
	while (temp != NULL) {
		printf("Address: %s + status: %c + pid: %d\n",temp->address,temp->status, temp->pid);		
		temp = temp->next;
	}
}

/*
 * Delete list's l first node
 */
void deleteFirstNode(List* l){
	Node* temp = l->first->next;
	free(l->first->address);
	free(l->first);
	l->first = temp;
	l->size--;
}

/*
 * Destroying the list by deleting the first node until list is empty
 */
void destroyList(List* l){
	for (int i=0; i < l->size; i++) 
		deleteFirstNode(l);
	free(l);
}

/*
 * Create and initialize a new node
 */
Node *createNode (char *addr, char stat, int id) {
	Node *n;
	if ((n = (Node *) malloc(sizeof(Node))) == NULL) {
		perror("Node's allocation failed");
		exit(-1);
	}
	setNode(n, addr, stat, id);
	return n;
}

/*
 * Clear the contents of node n
 */
void clearNode (Node *n) {
	n->address = NULL;
	n->status = '0';
	n->pid = 0;
	n->next = NULL;
} 

/*
 * Set the contents of node n
 */
void setNode (Node *n, char *addr, char stat, int id) {
	if ((n->address = (char *) malloc((strlen(addr)+1)*sizeof(char)))==NULL) {
		perror("Allocation failed");
		exit(-1);
	}
	strcpy(n->address,addr);
	n->status = stat;
	n->pid = id;
}