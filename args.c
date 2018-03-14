#include <stdio.h>
#include <stdlib.h>
#include "args.h"

/*
 * There are some limitations that have to be checked
 */
void checkArguments (int argc, char **argv, int *k, int *frames, int *q, int *max) {
	if (argc == 5) {
		if (!isNumeric(argv[1]) || !isNumeric(argv[2]) || !isNumeric(argv[3]) || !isNumeric(argv[4])) {
			printf("Arguments should be numbers\n");
			exit(-1);
		}
		*k = atoi(argv[1]);
		*frames = atoi(argv[2]);
		*q = atoi(argv[3]);
		*max = atoi(argv[4]);
		printArguments (*k, *frames, *q, *max);
		if ((*frames) < 2*(*k)) {
			printf("Main memory frames must be at least equal to 2 times k (frames >= k)\n");
			exit(-1);
		}
	}
	else {
		printf("Invalid number of arguments : <k> <frames> <q> <max>\n");
		exit(-1);
	}
}

/*
 * Print the given arguments
 */
void printArguments (int k, int frames, int q, int max) {
	printf("\n-------------------------------------------------------------------------------\n");
	printf("\tINPUT\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("Maximum page faults : %d\n",k);
	printf("Main memory frames : %d\n",frames);
	printf("Change trace after : %d\n",q);
	printf("Total number of memory references : %d \n", max);
	printf("-------------------------------------------------------------------------------\n\n\n");	
}

/*
 * Check if a string contains only numbers
 */
int isNumeric (const char *str) {
    while(*str != '\0') {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}