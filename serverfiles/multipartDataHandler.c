#include "binaryReaderWriter.c"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include "bufferSetUp.c"

#define END_OF_FILE 0

// This scetion will provide a set of tools thta can be used to handle multipart data handling



char* trsCSTRING_TO_SEQ(char* cString,uint size)
{
    char* ptr = malloc(size-1);
    for(int i = 0; i<size-1;i++){
        ptr[i] = cString[i];
    }

    return ptr;
}


void pChars(char* seq, int seqS)
{
    printf("CAUTION PRINT SEQUENCE !!!\n");
    for(int i = 0; i<seqS;i++){
        printf("%c",seq[i]);
    }
    printf("\n");
}



// Note this function returns a char ptr of the boundary string length can be found using
// Dont forget to free the memory after usage
char* findBoundaryString(char* BINARY_DATA, uint DATA_SIZE, int* sizeForSequence)
{
    char* b = "boundary=";
    char* b_seq = trsCSTRING_TO_SEQ(b, 10);
    // pChars(b_seq, 9);

    int offset = findSequenceInBinaryData(BINARY_DATA, DATA_SIZE, b_seq,9,0);
    offset+=9;

    char temp[200];
    int SIZE = 0;
    printf("PRINT THE BD STRING FROM BINARY_DATA\n");
    while(BINARY_DATA[offset]!='\r'){
        temp[SIZE] = BINARY_DATA[offset];
        ++offset;
        ++SIZE;
    }
    temp[offset] = '\0';

    char* RETURN_BD_STRING_BY_DEF = trsCSTRING_TO_SEQ(temp, SIZE+1);
    *sizeForSequence = SIZE;

    free(b_seq);
    return RETURN_BD_STRING_BY_DEF;
}


char* genStartingBD_STRING(char* BINARY_DATA, uint DATA_SIZE, int* seqSize)
{
    int s;
    char* str = findBoundaryString(BINARY_DATA, DATA_SIZE, &s);

    char* ptr = malloc(s+2);
    ptr[0] = '-';
    ptr[1] = '-';

    int ss = 0;
    for(int i = 2;i<s+2;i++){
        ptr[i] = str[ss];
        ++ss;
    }

    *seqSize = s+2;

    free(str);
    return ptr;
}


int getIndexWhereBoundaryStringStarts(char* DATA,uint DATA_SIZE)
{
    int size;
    char* ptr = genStartingBD_STRING(DATA, DATA_SIZE, &size); // pls free later

    int index = findSequenceInBinaryData(DATA, DATA_SIZE, ptr, size, 0);

    free(ptr);
    return index;
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
    char* ptr_bd_string = genStartingBD_STRING(buffer, buffer_size,&size);

    printf("BD STRING MODE SEARCH ACTIVE\n");

    for(int i = 0; i<size; i++){
        printf("%c",ptr_bd_string[i]);
    }
    printf("\n");

    char* ptrSend = malloc(size+2);

    for(int i = 0; i<size;i++){
        ptrSend[i] = ptr_bd_string[i];
    }

    ptrSend[size] = '-';
    ptrSend[size+1] = '-';
    free(ptr_bd_string);
    

    int res = findSequenceInBinaryData(buffer,buffer_size, ptrSend,size+2, 0);
    /*
    printf("THIS IS ATEST FOR THE ENHD BOUNDARY STRING PLS COMPARE IT WITH UR BROWSERS\n");
    for(int i = 0; i<size+2; i++){
        printf("%c",ptrSend[i]);
    }
    printf("\n");
    */

    free(ptrSend);
    printf("BD STRING MODE DISABLED\n");
    if(res==-1){ return -1; }
    if(res!=-1){return res;}
    return -1;
}


// WARNING: INPUT MUST BE SEQUENCE OF CHARS AND NOT A C STRING !!!
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








// WARNING: NEEDS TO BE CHECKED                              returns the index at which the actual content starts at
int calcOffsetIndex(char* data, int dSize)
{
    char seq[4];
    seq[0] = '\r';
    seq[1] = '\n';
    seq[2] = '\r';
    seq[3] = '\n';
    
    char* str = "Content-Disposition:";
    char* seq_str = trsCSTRING_TO_SEQ(str, 21);  // pls free it later

    int index = findSequenceInBinaryData(data, dSize, seq_str, 13, 0);
    printf("%dContent dispo TYPE AT INDEX: \n",index);
    printf("%c\n",data[index]);


    index = findSequenceInBinaryData(data, dSize, seq, 4, index);
    printf("KAKAKAKAKAKA\n");
    printf("%c\n",data[index]);

    index+=4;

    for(int i = 0;i<20; i++){
        printf("%c",seq_str[i]);
    }
    printf("so i guess it worked ?\n");

    free(seq_str);
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






// Prepare Buffer and BufferSize for writng data to it
void* prepareBuffer(char* BUFF, uint BUFF_S, int* whereBIN_STARTS_AT, int* n_size)
{
    int end = searchForEndBoundaryString(BUFF, BUFF_S);
    if(end == -1){
        printf("FATAL ERROR AT FETCHING E BD STRING !!!!\n");
    }
    

    int new_buffer_size = 0;

    //implement new size calculation
    new_buffer_size = (end+1)-(*whereBIN_STARTS_AT+1);

    char* WRITE = malloc(new_buffer_size);


    int ii = 0;
    for(int i = *whereBIN_STARTS_AT; i<end; i++){
        WRITE[ii] = BUFF[i];
        ++ii;
    }


    *n_size = new_buffer_size;
    return WRITE;
}


void BEST_CASE_MODE(char* BIN_BUFF,uint BIN_SIZE)
{
    int offset = calcOffsetIndex(BIN_BUFF, BIN_SIZE);

    int seq_size;
    char* fileName = findFileName(BIN_BUFF, BIN_SIZE, &seq_size);

    // TRANSLATE FILENAME INTO C STRING BASED FILE_PATH
    int size;
    char* filePath = transformToC_StringPath(fileName, seq_size, &size);


    int n;
    char* n_buffer = (char*)prepareBuffer(BIN_BUFF, BIN_SIZE, &offset,&n); // free buffer later pls

    writeBinaryToDisk(filePath,n_buffer,n-2);
    free(n_buffer);
}


// BRO I HAVE NO IDEA WHY I WROTE THAT I SIMPLY JUST CANT REMEBER IT
// MAYBE REMOVE THAT FILE
void h(char* buffer, int buffer_size, int bytesRead)
{
    int index = calcOffsetIndex(buffer,buffer_size);
    char* spaced = &buffer[index];


}











// FOR SOME REASON ENTERS A NEVER ENDING LOOP ERR NOT FIXED YET
// WARNING SOME PARAMS ARE NOT NEEDED YET ADDED TO LATER ON ADD ERROR HANDLING
// Handler will come in future WARNING HANDLER BLOWS UP MEMORY ISSUES FIX LATER
void WorstCase(char* DATA, uint DATA_SIZE, int bytesRead, int fd, char* EXTRACTED_DATA_BUFFER, uint EXTRACTED_DATA_BUFFER_SIZE)
{
    int BYTES_READ = bytesRead;
    u_int32_t LAST_WRITTEN_INDEX = 0;

    printf("HAS ENTERED\n");

    while(1){
        printf("THE LAST WRITTEN INDEX IS:%d\n",LAST_WRITTEN_INDEX);
        for(int i = 0; i < BYTES_READ; i++){
            EXTRACTED_DATA_BUFFER[LAST_WRITTEN_INDEX] = DATA[i];
            ++LAST_WRITTEN_INDEX;
        }
        BUFFER_RELOAD(DATA,DATA_SIZE,fd,&BYTES_READ);
        printf("%d\n",BYTES_READ);
        printf("-\n");
        if(searchForEndBoundaryString(EXTRACTED_DATA_BUFFER,EXTRACTED_DATA_BUFFER_SIZE)!=-1){
            break;
        }
    }
    printf("ENTERING BEST CASE SCENARIO\n");
    BEST_CASE_MODE(EXTRACTED_DATA_BUFFER, EXTRACTED_DATA_BUFFER_SIZE);
}





// JUST A DUMMY REMOVE LATER ON
void WorstCaseM(char* DATA, uint DATA_SIZE, int* bytesRead, int fd)
{
    // Defines BD END
    //int BYTES_READ = *bytesRead;
    int bd_size;
    char* bd = genStartingBD_STRING(DATA,DATA_SIZE,&bd_size);
    char* bd_end = malloc(bd_size+2);     // WARNING PLS FREE AT END
    for(int i = 0; i<bd_size;i++){
        bd_end[i] = bd[i];
    }
    bd_end[bd_size] = '-';
    bd_end[bd_size+1] = '-';
    free(bd);
    int bd_end_size = bd_size+4;
    // FETCH FILEPATH
    int fileName_seq;
    char* fileName = findFileName(DATA, DATA_SIZE, &fileName_seq);        // WARNING PLS FREE LATER !!!!
    int s;
    char* filePath = transformToC_StringPath(fileName,fileName_seq, &s);
    free(fileName);
    // TEST FINAL BD END STRING lol
    printf("HELLO THIS IS A TEST TO SEE THE RES OF MY NEW FUNCTION PLS CHECK IT !!!!!!\n");
    pChars(bd_end, bd_end_size);
    // FIRST WRITE
    
    // Creates the file and writes the first chunk into it
    int offset = calcOffsetIndex(DATA, DATA_SIZE);
    int firstSize = *bytesRead-(offset+1);
    char* foo = &DATA[offset];
    writeBinaryToDisk(filePath, foo, firstSize);
    
    int call = 1;
    BUFFER_RELOAD(DATA, DATA_SIZE, fd, bytesRead);
    // MID WRITE
    while(findSequenceInBinaryData(DATA,DATA_SIZE,bd_end,bd_end_size,0)==-1){
        printf("Call Number: %d\n",call);
        ++call;
        OffsetWriter(filePath,DATA,*bytesRead,ReturnFileSize(filePath));
        BUFFER_RELOAD(DATA,DATA_SIZE,fd, bytesRead);
    }



    printf("Do we get here ?\n");

    // LAST WRITE
    OffsetWriter(filePath, DATA, *bytesRead-bd_end_size, ReturnFileSize(filePath));
    free(filePath);
}





































/*

// FUCK THIS SHIT THE FUCK U CANT WRITE SHIT TO DISK BUT U CAN WRITE IT TO DISK WITH OVERFLOW WHO THE FUCK GONNE DEBUG THAT ???
// WARNING: THIS FUNCTION IS STILL EXPERIMENTAL AND WILL NEED TO BE FIXED OVER THE NEXT SEVERA MONTH OR SO
void postHandling(char* BUFFER, int BUFFER_SIZE, int* bytesRead)
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


        int n_buff_size;
        char* n_buff = (char*)prepareBuffer(BUFFER, BUFFER_SIZE, &offset, &n_buff_size);

        // TEST1
        printf("--------------------------------PP\n");
        for(int i = 0; i<n_buff_size; i++){
            printf("%c",n_buff[i]);
        }
        printf("\n");
        printf("---------------------------------------PPE\n");
        // TEST1 END

        int elementNumber = offset+1;

        // WARNING: CALC DATA RL SIZE ISSUE FIX NEEDE ASAP
        int calcSize = *bytesRead-elementNumber;

        // trnsformation of fileName
        int s;
        char* filePath = transformToC_StringPath(fileName,fileNameSize,&s); // pls free later



        printf("%cAFTER SHIFT",shiftedBuffer[0]);
        //let us try to write
        writeBinaryToDisk(filePath,n_buff,n_buff_size);    // lets see if it blow up lol YES IT DOES LOL ._.


        free(n_buff);
        free(fileName);
        free(filePath);
    }

    printf("Nope\n");
    
}

*/



























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
