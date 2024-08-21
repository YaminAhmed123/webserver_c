#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>



void BUFFER_RELOAD(char* BUFFER, uint BUFFER_SIZE, int fd,int* bytesRead)
{
    memset(BUFFER,0,BUFFER_SIZE);
    *bytesRead = read(fd,BUFFER,BUFFER_SIZE);
}