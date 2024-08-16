// this file defines a set of functions to search for a sequence of data in binary files
#include <stdio.h> 
#include <sys/types.h>



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


// Use that function to write into memory
void writeBinaryToDisk(char* fileName, char* DATA, uint DATA_SIZE)
{
    FILE* file = fopen(fileName, "wb");

    fwrite(DATA,sizeof(char), DATA_SIZE, file);
}

