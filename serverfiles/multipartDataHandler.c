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

int getIndexWhereBoundaryStringIs(char* DATA,uint DATA_SIZE)
{
    int size;
    char* ptr = findBoundaryString(DATA,DATA_SIZE,&size); // pls free later

    int index = findSequenceInBinaryData(DATA, DATA_SIZE, ptr, size, 0);
    index+=size;

    int rl_index = findSequenceInBinaryData(DATA, DATA_SIZE, ptr, size, index);

    free(ptr);
    return rl_index;
}


// Basically same as BoundaryString but val is changed to Content-Length:
char* findContentLength(char* BINARY_DATA, uint DATA_SIZE, int* sizeForSequence)
{
    char* b = "Content-Length: ";
    char boundary[strlen(b)];

    for(int i = 0; i< strlen(b); i++)
    {
        boundary[i] = b[i];
    }


    
    // search binary for the sequence
    int index = findSequenceInBinaryData(BINARY_DATA, DATA_SIZE,boundary, strlen(b),0);

    if(index == -1){return NULL;}

    index+=16;

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




char* findFileName(char* BINARY_DATA, uint DATA_SIZE, int* sizeForSequence)
{

    // Set like this casue compiler does not support it that way
    char b[11];
    b[0] = 'f';
    b[1] = 'i';
    b[2] = 'l';
    b[3] = 'e';
    b[4] = 'n';
    b[5] = 'a'; 
    b[6] = 'm';
    b[7] = 'e';
    b[8] = '=';
    b[9] = '"';
    b[10] = '\0';


    char boundary[strlen(b)];

    for(int i = 0; i< strlen(b); i++)
    {
        boundary[i] = b[i];
    }


    
    // search binary for the sequence
    int index = findSequenceInBinaryData(BINARY_DATA, DATA_SIZE,boundary, strlen(b),0);

    if(index == -1){return NULL;}

    index+=10;

    char tempBuffer[1000];
    memset(tempBuffer,0, sizeof(tempBuffer));
    int i = 0;
    while(BINARY_DATA[index] != '"'){
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


int searchForEndBoundaryString(char* buffer, int buffer_size)
{
    int size;
    char* ptr_bd_string = findBoundaryString(buffer, buffer_size,&size);

    char* ptrSend = malloc(size+2);
    ptrSend[size] = '-';
    ptrSend[size+1] = '-';
    free(ptr_bd_string);
    

    int res = findSequenceInBinaryData(buffer,buffer_size, ptrSend,size+2, 0);

    if(res==-1){ return -1; }
    if(res!=-1){return res;}
    return -1;
}


int getContentLengthAsNumber(char* data, int data_size)
{
    int sum;
    char* n = findContentLength(data, data_size, &sum);

    char num[sum+1];
    for(int i = 0; i<sum; i++){
        num[i] = n[i];
    }
    num[sum] = '\0';

    free(n);

    return atoi(num);
}



void postHandling(char* BUFFER, int BUFFER_SIZE)
{
    // Get MethaData first
    int ContentLength = getContentLengthAsNumber(BUFFER, BUFFER_SIZE);

    int fileNameSize;
    char* fileName = findFileName(BUFFER, BUFFER_SIZE, &fileNameSize);

    int BD_STRING_INDEX = getIndexWhereBoundaryStringIs(BUFFER, BUFFER_SIZE);


    
    // Check if best case scenario happened 
    int happy = searchForEndBoundaryString(BUFFER, BUFFER_SIZE);
    if(happy!=-1){
        // be happy :) and write the relevant buffer data to disk :)))))


    }


}



























// Bug found the boundary string is not the end boundary string resulting in an immediate exit

// CAUTION THIS METHOD CANNOT BE USED IT HAS AT SOME POINT A BUG THAT HAS NOT BEEN IDENTIFIED YET
// A future implement will come where it will simply read to Content-Length


/*
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

*/
