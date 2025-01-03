// this file defines a set of functions to search for a sequence of data in binary files
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h>



// Searches binary data and return the index of the bindary data at which the sequence starts at
int findSequenceInBinaryData(char* BINARY_DATA,int dataSize, char* sequence,int sequenceSize, int offset)
{
    int init_I;
    for(int i = offset; i<dataSize; i++){

        init_I = i;

        for(int j = 0; j < sequenceSize; j++){

            if(BINARY_DATA[i]==sequence[j]){

                // let is pass
                if(j == sequenceSize-1){return init_I;}
                ++i;
            } else {
                i = init_I;
                break;
            }
        }
    }
    return -1;
}



// WARNING: THIS FUNCTIONS TURNS OUT TO BE WAY TO SIMPLE FOR THE USECASE PLEASE MAKE NEW FUNCTION WITH OFFSETTING          Use that function to write into memory
void writeBinaryToDisk(char* fileName, char* DATA, uint DATA_SIZE)
{
    FILE* file = fopen(fileName, "wb");

    fwrite(DATA,1, DATA_SIZE, file);
    fclose(file);     // Bro if u would no how much time i wasted cause i fogot to add that line WASTED_TIME = 7h
}



void OffsetWriter(char* fileName,char* DATA,uint DATA_SIZE,int offset)
{
    FILE* file = fopen(fileName, "r+b");

    if(offset!=0){
        fseek(file,offset,SEEK_SET);
    }

    fwrite(DATA, 1, DATA_SIZE, file);
    fclose(file);
}

long ReturnFileSize(char* filePath)
{
    FILE* file = fopen(filePath,"rb");
    fseek(file,0,SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}
