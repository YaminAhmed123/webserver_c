#include <stdio.h>

void readFile(char* FILEPATH, char* BUFFER, int BUFFER_SIZE)
{
    FILE* p_FILE = fopen(FILEPATH, "r");
    int charsRead = fread(BUFFER,1,BUFFER_SIZE-1, p_FILE);

    BUFFER[charsRead] = '\0';
    fclose(p_FILE);
}


struct reader{
    char* FILEPATH;
    char FILE_BUFFER[1024]; //take in note that this is a static size this might blow up when loading large files
};

typedef struct reader READER;
