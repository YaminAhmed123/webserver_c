#include <stdio.h>
#include <string.h>
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

    int res = findSequenceInBinaryData(buffer,20,sequences,10,0);

    printf("%d\n",buffer[5+2]);
    printf("%d\n",buffer[2+res]);

    //test sequence
    char buffer2[10];
    char* seq = "seq";

    memset(buffer2,1,10);

    // fake seq
    buffer2[0] = 's';
    buffer2[1] = 'e';
    buffer2[2] = 'q';

    // real seq
    buffer2[5] = 's';
    buffer2[6] = 'e';
    buffer2[7] = 'q';
    buffer2[8] = '\0';

    int res2 = findSequenceInBinaryData(buffer2, 10, seq, 4,0);


    // test passed not that memset 0 = \0 as char
    // expected result = 5
    printf("%d\n",res2);


    // WARNING: PLEASE CHECK THE FILES FROM multipartDataHandler.c !!!
    
    

}
