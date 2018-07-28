# Flush when full 
Our program simulates a memory management system using real reference systems. The files bzip.trace and gcc.trace contain the 
references, one at a line. Each reference consists of a hex memory address and a char, R (read) or W (write). The program reads
the references and simulates the page table mechanism. The simulator must check if the page is already stored at the main memory. If the memory is full and the simulator has to replace a page, it uses the 
Flush When Full (FWF) algorithm. The FWF assumes that the reference trace is seperated into blocks. While scanning each block, 
the process can have at most k page faults. When the k+1 page fault appears, the process flushes the allocated frames.

Written in C. Contains makefile in each folder. Use `make` to compile and `make clean` to remove the object files and 
the executable. Needs exactly four arguments.\
Execution command: ./fwf *k *frames* *q* *max*, where \
*k* : Maximum page fault\
*frames* : Main memory frames\
*q* : Change trace (bzip, gcc) after q references\
*max*: Total number of memory references
