#include "binaryReaderWriter.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This scetion will provide a set of tools thta can be used to handle multipart data handling



// Note this function returns a char ptr of the boundary string length can be found using
// Dont forget to free the memory after usage
char* findBoundaryString(char* BINARY_DATA, uint DATA_SIZE, int* sizeForSequence)
{
    char* b = "boundary=";
    char boundary[strlen(b)];

    for(int i = 0; i< strlen(b); i++)
    {
        boundary[i] = b[i];
    }


    
    // search binary for the sequence
    int index = findSequenceInBinaryData(BINARY_DATA, DATA_SIZE,boundary, strlen(b));

    if(index == -1){return NULL;}

    index+=9;

    char tempBuffer[1000];
    memset(tempBuffer,0, sizeof(tempBuffer));
    int i = 0;
    while(BINARY_DATA[index] != '\r'){
        tempBuffer[i] = BINARY_DATA[index];
        ++index;
        ++i;
    }


    char* boundaryString = malloc(sizeof(char)*strlen(tempBuffer));

    for(int i = 0; i<strlen(tempBuffer);i++){
        boundaryString[i] = tempBuffer[i];
    }
    *sizeForSequence = strlen(tempBuffer);
    return boundaryString;
}



//This part of the file will provide a set that calls an relaods the buffer till boundary was found

void doStuff(char* dBuffer, uint dBufferSize)
{
    // fetch Boundary String out of buffer
    int SEQ_SIZE;
    char* BOUNDARY_STRING = findBoundaryString(dBuffer, dBufferSize, &SEQ_SIZE);

    
}