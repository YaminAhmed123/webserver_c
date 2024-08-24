#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>



void BUFFER_RELOAD(char* BUFFER, uint BUFFER_SIZE, int fd,int* bytesRead)
{
    memset(BUFFER,0,BUFFER_SIZE);
    *bytesRead = recv(fd,BUFFER,BUFFER_SIZE,0);
}



void recursive_BUFFER_RELOAD(char* BUFFER, uint BUFFER_SIZE, int fd,int* bytesRead)
{
    if(*bytesRead==-1)
    {
        BUFFER_RELOAD(BUFFER, BUFFER_SIZE,  fd, bytesRead);
        recursive_BUFFER_RELOAD(BUFFER, BUFFER_SIZE, fd, bytesRead);
    } else{
        // U FWEE MY BOY :)
    }
}

