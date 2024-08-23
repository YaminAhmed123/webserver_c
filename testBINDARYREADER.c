#include "serverfiles/binaryReaderWriter.c"


int main()
{
    char txt[4];
    txt[0] = 'h';
    txt[1] = 'a';
    txt[2] = 'l';
    txt[3] = 'l';

    char txt2[2];
    txt2[0] = 'o';
    txt2[1] = 'o';

    char* fileName = "TestFileInBinaryMode.txt";


    writeBinaryToDisk(fileName,txt,4);
    OffsetWriter(fileName,txt2,2,ReturnFileSize(fileName));

    // LOOK IF IT ACTUALLY WORKS WITH CHECKING FILE MANUALLY

    return 0;
}
