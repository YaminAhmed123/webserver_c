#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

    int server_fd, new_socket;
    struct sockaddr_in server_address, client_address;
    int addrlen = sizeof(client_address);
    char buffer[BUFFER_SIZE] = {0};
    char *http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from server!";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_fd, 5);


    new_socket = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*)&addrlen);


    
    read(new_socket, buffer, BUFFER_SIZE);


    
    send(new_socket, http_response, strlen(http_response), 0);
   

   
    close(new_socket);
    close(server_fd);

    return 0;
}
