# Flush when full 
This program simulates a memory management system using real system's references. The files bzip.trace and gcc.trace contain the references, one at a line. Each reference consists of a hex memory address and a char, R (read) or W (write). The program reads the references and simulates the page table mechanism. The simulator must check if the page is already stored at the main memory. If the memory is full and the simulator has to replace a page, it uses the Flush When Full (FWF) algorithm. The FWF assumes that the reference trace is seperated into blocks. While scanning each block, the process can have at most k page faults. When the k+1 page fault appears, the process flushes the allocated frames.<br/>

Written in C++, Ubuntu 16.04.3 LTS.

## Execution command 
./fwf *k *frames* *q* *max* <br/>where<br/>
*k* : Maximum page fault<br/>
*frames* : Main memory frames<br/>
*q* : Change trace (bzip, gcc) after q references<br/>
*max*: Total number of memory references

## Makefile
- `make` to compile
- `make clean` to remove the object files and the executable.
