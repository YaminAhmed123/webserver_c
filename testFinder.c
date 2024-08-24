#include <stdio.h>
#include "serverfiles/binaryReaderWriter.c"


int main()
{
    printf("THIS WILL TEST THE FIDN FUNCTION IF IT IS CAPABLE OF FINDING A SEQ IF IT AT BD END\n");

    char arr[100];
    arr[98] = 'k';
    arr[99] = 'j';

    char seq[2];
    seq[0] = 'k';
    seq[0] = 'j';

    int res = findSequenceInBinaryData(arr,100,seq,2,0);

    if(res!=-1){
        printf("Success !\n");
    } else{
        printf("Test Failed\n");
    }

    return 0;
}
