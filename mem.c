#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "mem.h"
#include "types.h"

/*
 * Page table has two blocks, one block for each trace (bzip, gcc). For each reference, search in the pagetable.
 * If reference not found in the proper block, there is a page fault and this reference has to be inserted in the page table in the proper block.
 * If the block is full, we have to empty this block and then insert the new reference.
 */
void simulateFWF(List *list, const int k, const int frames, const int max) {

	int pagefaults=0, readsfromdisk=0, writesondisk=0, pf1=0, pf2 =0, counter=0;
	Node *pagetable;
	char *addr;
	if ((pagetable = (Node*) malloc(frames*sizeof(Node)))==NULL) {
		perror("Cannot allocate pagetable");
		exit(-1);
	}
	for (int i=0; i<frames;i++) {
		clearNode (&pagetable[i]);
	}
	while (list->size) {
		if ((addr = (char*) malloc((strlen(list->first->address) + 1)*sizeof(char)))==NULL) {
			perror("Malloc for address failed");
			exit(-1);
		}
		strcpy(addr,list->first->address);
		char stat = list->first->status;
		int id = list->first->pid;
		int found = search(pagetable,frames,addr,id);
		if (found == -1) {
			pagefaults ++;
			readsfromdisk++;
			if (id == BZIP) {
				pf1++;
				if (pf1 == k+1) {
					counter = flushPagetable(pagetable,frames,id);
					writesondisk += counter;					
					pf1=0;
					setNode (&pagetable[0], addr, stat, BZIP);
				}
				else {
					tryToInsert(pagetable,frames,addr,stat,id);
				}
			}
			else if (id==GCC) {
				pf2++;
				if (pf2 == k+1) {
					counter = flushPagetable(pagetable,frames,id);
					writesondisk += counter; 					
					pf2=0;
					setNode (&pagetable[k], addr, stat, GCC);
				}
				else {
					tryToInsert(pagetable,frames,addr,stat,id);
				}
			}
		}
		else {
			if (stat=='W') {
				pagetable[found].status='W';
			}	
		}
		free(addr);	
		deleteFirstNode(list);
	}
	for (int i=0; i<frames; i++) {
		if (pagetable[i].address!=NULL) 
			free(pagetable[i].address);
	}
	free(pagetable);
	printStats (writesondisk, readsfromdisk, pagefaults, max, frames);

}

/*
 * Search if a reference is stored in the pagetable
 * Returns the position of the reference in the page table, otherwise -1
 */
int search(Node *pagetable, int size, char *addr, int id) { 
	
	int lower, upper;

	if (id == BZIP) { 
		lower = 0;
		upper = size/2;
	}
	else {
		lower = size/2;
		upper = size;
	}
	for (int i=lower; i < upper; i++) {
		if (pagetable[i].address==NULL) return -1;	
		if (strcmp(pagetable[i].address,addr)==0) return i;
	}
	return -1;
}

/*
 * Flush the upper or the lower half of the pagetable base on the id argument
 * Returns the amount of entries that have to be written to the disk
 */
int flushPagetable(Node *pagetable,int size,int id) {
	
	int lower, upper, counter=0;

	if (id == BZIP) {
		lower = 0;
		upper = size/2;
	}
	else {
		lower = size/2;
		upper = size;
	}
	for (int i=lower; i < upper; i++) {
		if (pagetable[i].address != NULL) {
			if (pagetable[i].status=='W') counter++;
			free(pagetable[i].address);
			clearNode (&pagetable[i]);
		}
	}
	return counter;
}

/*
 *
 */
void tryToInsert(Node *pagetable, int size, char *addr, char stat, int id) {
	
	int lower, upper;
	
	if (id == BZIP) {
		lower = 0;
		upper = size/2;
	}
	else {
		lower = size/2;
		upper = size;
	}
	for (int i=lower; i < upper; i++) {
		if (pagetable[i].address == NULL) {
			setNode (&pagetable[i], addr, stat, id);
			return;
		}
	}
}


/*
 * Print the final stats of the Flush When Full simulation
 */
void printStats (int writesondisk, int readsfromdisk, int pagefaults, int max, int frames) {
	printf("\n-------------------------------------------------------------------------------\n");
	printf("\tOUTPUT\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("Writes on disk : %d\n",writesondisk);
	printf("Reads from disk : %d\n",readsfromdisk);
	printf("Total page faults : %d\n",pagefaults);
	printf("Total number of memory references : %d \n", max);
	printf("Main memory frames : %d\n",frames);
	printf("-------------------------------------------------------------------------------\n\n\n");
}