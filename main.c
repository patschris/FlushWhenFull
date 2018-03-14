#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "files.h"
#include "mem.h"
#include "args.h"

int main (int argc, char **argv) {
	int k, frames, q, max;		
	checkArguments (argc, argv, &k, &frames, &q, &max);
	printf("Simulating ... \n\n\n");
	List *lista = createList();
	inputFiles(lista, q, max);
	simulateFWF(lista,k,frames,max);
	destroyList(lista);
	return 0;
}