#ifndef _mem_
#define _mem_

void simulateFWF(List *, const int, const int, const int);
int search(Node *, int, char *, int);
int flushPagetable(Node *, int, int);
void tryToInsert(Node *, int, char *, char, int);
void printStats (int, int, int, int, int);

#endif