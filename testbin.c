#include <stdio.h>
#include "serverfiles/binaryReaderWriter.c"

int main()
{
    char buffer[20];
    for(int i = 0; i<10; i++){
        buffer[i+5] = i;
    }


    char sequences[10];
    for(int i = 0; i<10; i++){
        sequences[i] = i;
    }

    int res = findSequenceInBinaryData(buffer,20,sequences,10);

    printf("%d\n",buffer[5+2]);
    printf("%d\n",buffer[2+res]);


}
