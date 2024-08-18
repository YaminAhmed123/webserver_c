#include "binaryReaderWriter.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>

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

    for(int i = 0; i<size;i++){
        ptrSend[i] = ptr_bd_string[i];
    }

    ptrSend[size] = '-';
    ptrSend[size+1] = '-';
    free(ptr_bd_string);
    

    int res = findSequenceInBinaryData(buffer,buffer_size, ptrSend,size+2, 0);

    for(int i = 0; i<size+2; i++){
        printf("%c",ptrSend[i]);
    }
    printf("\n");

    free(ptrSend);
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



char* trsCSTRING_TO_SEQ(char* cString,uint size)
{
    char* ptr = malloc(size-1);
    for(int i = 0; i<size-1;i++){
        ptr[i] = cString[i];
    }
    return ptr;
}




// WARNING: NEEDS TO BE CHECKED                              returns the index at which the actual content starts at
int calcOffsetIndex(char* data, int dSize)
{
    char seq[4];
    seq[0] = '\r';
    seq[1] = '\n';
    seq[2] = '\r';
    seq[3] = '\n';
    
    char* str = "Content-Type:";
    char* seq_str = trsCSTRING_TO_SEQ(str, 14);  // pls free it later

    int index = findSequenceInBinaryData(data, dSize, seq_str, 13, 0);
    index = findSequenceInBinaryData(data, dSize, seq_str, 13, index);

    index+=4;


    return index;
}




char* transformToC_StringPath(char* fileName, int fSize, int* s)
{
    char spam[12];
    spam[0] = 'O';
    spam[1] = 'N';
    spam[2] = 'L';
    spam[3] = 'I';
    spam[4] = 'N';
    spam[5] = 'E';
    spam[6] = '/';
    spam[7] = 'f';
    spam[8] = 'i';
    spam[9] = 'l';
    spam[10] = 'e';
    spam[11] = 's';

    char* ptr = malloc(12+fSize+2);

    for(int i = 0; i < 12; i++){
        ptr[i] = spam[i];
    }
    ptr[12] = '/';

    int xo = 13;
    for(int i = 0; i<fSize; i++){
        ptr[xo] = fileName[i];
        ++xo;
    }

    ptr[12+fSize+1] = '\0';
    printf("%s\n",ptr);
    return ptr;
}










// WARNING: THIS FUNCTION IS STILL EXPERIMENTAL AND WILL NEED TO BE FIXED OVER THE NEXT SEVERA MONTH OR SO
void postHandling(char* BUFFER, int BUFFER_SIZE)
{
    // Get MethaData first
    int ContentLength = getContentLengthAsNumber(BUFFER, BUFFER_SIZE);

    int fileNameSize;
    char* fileName = findFileName(BUFFER, BUFFER_SIZE, &fileNameSize);

    int BD_STRING_INDEX = getIndexWhereBoundaryStringIs(BUFFER, BUFFER_SIZE);
    printf("%c\n",BUFFER[BD_STRING_INDEX]);

    
    // Check if best case scenario happened 
    int happy = searchForEndBoundaryString(BUFFER, BUFFER_SIZE);
    if(happy!=-1){
        printf("Happy has been entered\n");

        // be happy :) and write the relevant buffer data to disk :)))))
        int offset = calcOffsetIndex(BUFFER,BUFFER_SIZE);

        printf("Boom after Offset\n");

        
        char* shiftedBuffer = &BUFFER[offset];
        int elementNumber = offset+1;
        int calcSize = BUFFER_SIZE-elementNumber;

        // trnsformation of fileName
        int s;
        char* filePath = transformToC_StringPath(fileName,fileNameSize,&s); // pls free later


        //let us try to write
        writeBinaryToDisk(filePath,shiftedBuffer,BUFFER_SIZE); // lets see if it blow up lol
        free(fileName);
        free(filePath);
    }

    printf("Nope\n");
    
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
