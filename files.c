#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "files.h"
#include "types.h"

/*
 * Using two input files bzip.trace and gcc.trace
 * Reading q items from each file until max is reached
 */
void inputFiles (List* list, const int q, const int max) {
	FILE *fp1,*fp2;
	if ((fp1=fopen("bzip.trace","r"))==NULL) {
		perror("fopen bzip");
		exit(-1);
	}
	if ((fp2=fopen("gcc.trace","r"))==NULL) {
		perror("fopen gcc");
		exit(-1);
	}
	int count=0;	
	while(1) { 
		for (int i=0; i< q; i++) { 
			readLine(list,fp1,BZIP); 
			count++;
			if(count == max) break; 
		}
		if(count == max) break; 
		for (int i=0; i< q; i++) {
			readLine(list,fp2,GCC);
			count++;
			if(count == max) break;
		}
		if(count == max) break;
	}
	fclose(fp1); 
	fclose(fp2);
}

/* 
 * Reading the line a line from the input file
 * Breaking the line in two token using space as a delimeter
 */
void readLine(List *list, FILE *fp, const int num) {
	char *line=NULL, addr[9], status[2];
	size_t len = 0;
    ssize_t read;
	if ((read = getline(&line, &len, fp)) != -1) { 
		char *token = strtok(line, " "); // ti xwrizw sto keno
		strcpy(addr,token); // to prwto miso einai i dieuthinsi
    	token = strtok(NULL, " ");
		strcpy(status,token);
		insert(list,addr,status[0],num); // kai to vazw sti lista
		free(line);
    }
	else {
		perror("Error in getline");
		exit(-1);
	}
}
