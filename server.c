#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "serverfiles/function.c"
#include "serverfiles/simplereader.c"


#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

    struct sockaddr_in client;
    struct sockaddr_in server;
    int server_socket;
    int foop = sizeof(struct sockaddr_in);

    char buffer[BUFFER_SIZE];
    memset(buffer,0,sizeof(buffer));
    
    char* MSG = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Length: 0\r\n"
    "\r\n";


    memset(&server, 0, sizeof(struct sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    server_socket = socket(AF_INET,SOCK_STREAM,0);
    int bind_stat = bind(server_socket, (struct sockaddr*)&server, sizeof(struct sockaddr));

    if(bind_stat < 0){ printf("ERR binding\n"); }

    int listen_stat = listen(server_socket,1);
    if(listen_stat<0){printf("ERR listen\n");}
    int foo;


    //playground
    char* path = "ONLINE/index.html";
    READER reader;
    reader.FILEPATH = path;

    memset((void*)&reader.FILE_BUFFER,0,1024);
    readFile(reader.FILEPATH, reader.FILE_BUFFER,1024);
    printf("%s\n",reader.FILE_BUFFER);

    while(1)
    {
        foo = accept(server_socket,(struct sockaddr*)&client, (socklen_t*)&foop);
        int STATUS = read(foo,buffer, BUFFER_SIZE-1);

        if(STATUS < 0) { printf("WARNING: buffer data might be corrupted\n"); }
        buffer[STATUS] = '\0';


        printf("%s\n",buffer);
        send(foo, MSG, strlen(MSG),0);
        printf("HTTP RESPONSE WAS SEND\n");
        close(foo);
        memset(buffer,0,sizeof(buffer));
    }
    
    close(foo);
    return 0;
}
