#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

    struct sockaddr_in client;
    struct sockaddr_in server;
    int server_socket;
    int foop = sizeof(struct sockaddr_in);
    
    char* MSG = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Length: 0\r\n"
    "\r\n";


    memset(&server, 0, sizeof(struct sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    server_socket = socket(AF_INET,SOCK_STREAM,0);
    bind(server_socket, (struct sockaddr*)&server, sizeof(struct sockaddr));

    listen(server_socket,1);
    int foo = accept(server_socket,(struct sockaddr*)&client, (socklen_t*)&foo);
    

    while(foo)
    {
        send(foo, MSG, strlen(MSG),0);
        printf("Sending shit to client\n");
        close(foo);
        foo = accept(server_socket,(struct sockaddr*)&client, (socklen_t*)&foo);
    }
    

    return 0;
}
