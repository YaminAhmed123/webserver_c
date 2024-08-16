#include "binaryReaderWriter.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>

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
    int index = findSequenceInBinaryData(BINARY_DATA, DATA_SIZE,boundary, strlen(b),0);

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








// CAUTION THIS METHOD CANNOT BE USED IT HAS AT SOME POINT A BUG THAT HAS NOT BEEN IDENTIFIED YET
// A future implement will come where it will simply read to Content-Length
void* doStuff(char* dBuffer, uint dBufferSize, char* BIN_BUFF,int* HowMuchStuffWritten,int* fd)
{
    // fetch Boundary String out of buffer
    printf("BREAK NOT AT FETCH\n");
    int SEQ_SIZE;
    char* BOUNDARY_STRING = findBoundaryString(dBuffer, dBufferSize, &SEQ_SIZE);

    // Search for it in buffer NOTE skip the part where it defines boundary
    int indexAtSkip = findSequenceInBinaryData(dBuffer, dBufferSize, BOUNDARY_STRING, SEQ_SIZE, 0);
    int RealEndAt = findSequenceInBinaryData(dBuffer, dBufferSize, BOUNDARY_STRING, SEQ_SIZE, indexAtSkip+SEQ_SIZE);

    printf("BREAK NOT BEFORE BEST SCENARIO\n");
    // If best case scenario

    
    if(RealEndAt!=-1){
        for(int i = 0; i<dBufferSize;i++){
            BIN_BUFF[i] = dBuffer[i];
        }
        *HowMuchStuffWritten = dBufferSize;
        printf("DAMN U MAN ARE LUCKY\n");

        // prove it
        for(int i = RealEndAt; i<SEQ_SIZE; i++){
            printf("%c",dBuffer[i]);
        }
        printf(" \n");
        printf("%d\n",RealEndAt);

        free(BOUNDARY_STRING);
        return NULL;  
    }
    

    printf("BREAK NOT BEFORE LOOP\n");
    u_int64_t SUPER = 0;
    while(1){

        if(RealEndAt!=-1){
            for(int i = 0; i<dBufferSize; i++){
                BIN_BUFF[SUPER] = dBuffer[i];
                ++SUPER;
            }
            free(BOUNDARY_STRING);
            printf("PEE PEE WOOMP\n");
            return NULL;
        }
        if(RealEndAt==-1){

            for(int i = 0; i<dBufferSize; i++){
                BIN_BUFF[SUPER] = dBuffer[i];
                ++SUPER;
            }
            printf("HOOOB SHOOB\n");
            // Setup for the dBuffer
            memset(dBuffer, 0, dBufferSize);
            int stat = read(*fd,dBuffer,dBufferSize);
        }
    }
}

