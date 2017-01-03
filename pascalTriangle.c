#include "pascalTriangle.h"

/* Print a row of the triangle with the given values. */
void
printRow(int curRow, int numRows, unsigned int *vals)
{
#if LEFT_ALIGNED 
    /* TODO Determine how many characters the worst case could use. */
    char *rowText = (char*)malloc(numRows * LARGEST_NUM_LENGTH * sizeof(char));
    if(!rowText) exit(MEM_ALLOCATION_FAILED);

    /* The current location in the row. */
    int rowCounter = 0;

    /* Write the number followed by a tab for each element in the triangle. */
    for(int i = 0; i < curRow; i++)
    {
        /* Safely add a number to the line. */
        int added = snprintf(rowText + rowCounter, LARGEST_NUM_LENGTH, "%u", *(vals + i));

        /* If the amount added is too large, exit early. */
        if(added >= LARGEST_NUM_LENGTH) 
        {
            printf("Error: number too large.\n");
            exit(MEM_ALLOCATION_FAILED);
        }
        rowCounter += added;

        /* Replace trailing null with tab. */
        *(rowText + rowCounter++) = '\t';
    }

    /* Add null to end of string. */
    *(rowText + rowCounter) = (char) 0;

#else
    char *rowText = (char*)malloc((numRows + 1)*sizeof(char));
    if(!rowText) exit(MEM_ALLOCATION_FAILED);

    /* The current location in the row. */
    int rowCounter;
    /* The leading spaces to make a sexy triangle. */
    int numSpaces = numRows - curRow;

    /* Write leading spaces. */
    for(rowCounter = 0; rowCounter < numSpaces; rowCounter++)
        *(rowText + rowCounter)= ' ';

    /* Write single char followed by a space for each element in the triangle. */
    for(int i = 0; i < curRow; i++)
    {
        *(rowText + rowCounter++) = *(vals + i) % 10 + '0';
        *(rowText + rowCounter++) = ' ';
    }

    /* Add null to end of string. */
    *(rowText + --rowCounter) = (char) 0;

#endif
    /* Print to standard output. */
    printf("%s\n", rowText);

    free(rowText);
}

/* Creates the triangle. */
void
computeTriangle(int numRows)
{
    /* Allocate memory for creating rows of integers. */
    unsigned int *newRow = (unsigned int*)malloc(numRows*sizeof(int));
    unsigned int *oldRow = (unsigned int*)malloc(numRows*sizeof(int));
    if(!newRow || !oldRow) exit(MEM_ALLOCATION_FAILED);

    /* Print first row and initialize first element of newRow and oldRow. */
    *newRow = 1;
    *oldRow = 1;
    printRow(1,numRows, newRow);

    /* Print second row. */
    if(numRows > 1)
    {
        *(newRow + 1) = 1;
        printRow(2, numRows, newRow);
    }

    /* Iterate over all the rest of the rows. */
    for(int i = 2; i < numRows; i++)
    {
        /* Copy old array. */
        for(int j = 1; j < i; j++) *(oldRow + j) = *(newRow + j);

        /* Each element of the new array is the sum of the elements of the
         * previous array at the same location and the location plus one. */
        for(int j = 0; j + 1 < i; j++) 
            *(newRow + j + 1) = *(oldRow + j) + *(oldRow + j + 1);

        /* Put a one at the last element in the array. */
        *(newRow + i) = 1;

        /* Print the row. */
        printRow(i + 1,numRows, newRow);
    }

    free(newRow);
    free(oldRow);
}

int
main(int argc, char *argv[])
{
    /* Get the number of rows from the command line arguments. If the command
     * was called incorrectly, exit with invalid args status. */
    int numRows;
    if( !(argc == 2 && sscanf(argv[1], "%d", &numRows) && numRows > 0) ) {
        printf("error\n");
        exit(INVALID_ARGUMENTS);
    }

    computeTriangle(numRows);
}

