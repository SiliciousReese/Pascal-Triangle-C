#include <stdio.h>
#include <stdlib.h>

/* Failure codes. */
#define INVALID_ARGUMENTS 1
#define MEM_ALLOCATION_FAILED 2

/* Used to switch between a left aligned triangle which allow all characters
 * and a centered triangle that only allows single digits. */
#define LEFT_ALIGNED 1

#if LEFT_ALIGNED
    #define LARGEST_NUM_LENGTH 100
#endif

void computeTriangle(int);

void printRow(int, int, unsigned int*);

