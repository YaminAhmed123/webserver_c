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
#include "serverfiles/multipartDataHandler.c"


#define PORT 8080
#define BUFFER_SIZE 20000


int main() {
    // prepare large data Buffer
    char* LARGE_DATA_BUFFER = (char*)malloc(512 * 1024 * 1024);
    int LARGE_DATA_BUFFER_SIZE = 512*1024*1024;

    //prepare static buffers for frontend

    {
        char* FILEPATH_CSS = "ONLINE/index.css";
        char* FILEPATH_HTML = "ONLINE/index.html";
        char* FILEPATH_JS = "ONLINE/index.js";


        memset(HTML_BUFFER,0,sizeof(HTML_BUFFER));
        memset(CSS_BUFFER,0,sizeof(CSS_BUFFER));
        memset(JS_BUFFER,0,sizeof(JS_BUFFER));


        readFile(FILEPATH_HTML, HTML_BUFFER, sizeof(HTML_BUFFER));
        readFile(FILEPATH_CSS, CSS_BUFFER, sizeof(CSS_BUFFER));
        readFile(FILEPATH_JS, JS_BUFFER, sizeof(JS_BUFFER));
    }

    // display Buffers
    printf("%s\n",HTML_BUFFER);
    printf("%s\n",CSS_BUFFER);
    printf("%s\n",JS_BUFFER);
    printf("-----------------Backend LOGs-----------------\n\n");


    struct sockaddr_in client;
    struct sockaddr_in server;
    int server_socket;
    int foop = sizeof(struct sockaddr_in);

    char buffer[BUFFER_SIZE];
    memset(buffer,0,sizeof(buffer));
    
    char* http_response = "HTTP/1.1 200 OK\r\n\r\n";



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

    genHEADER_HTML();
    genHEADER_CSS();
    genHEADER_JS();



    while(1)
    {
        foo = accept(server_socket,(struct sockaddr*)&client, (socklen_t*)&foop);
        int STATUS = read(foo,buffer, BUFFER_SIZE);

        /*
        if(STATUS < 0) { printf("WARNING: buffer data might be corrupted\n"); }
        buffer[STATUS] = '\0';
        */
        
        // printf("%s",buffer);

        if( CHECK_REQUEST(buffer)== 'H' ) { SEND_HTML(foo); }
        if( CHECK_REQUEST(buffer)== 'C' ) { SEND_CSS(foo); }
        if( CHECK_REQUEST(buffer)== 'J' ) { SEND_JS(foo); }
        if( CHECK_REQUEST(buffer)== 'P' ) 
        {
            // cannot do that as it includes bin data as well printf("%s\n",buffer);

            /*
            int sum;
            void* checkVAL = doStuff(buffer,BUFFER_SIZE,LARGE_DATA_BUFFER,&sum,&foo);
            */

      
      
            // Test new impkement Content-Length function

            /*
            int xax;
            char* ptr = findContentLength(buffer, BUFFER_SIZE, &xax);

            for(int i = 0; i<xax; i++){
                printf("%c",ptr[i]);
            }
            printf("\n");

            free(ptr);
            */

            // find file name

            /*
            int sum;
            char* ptx = findFileName(buffer,BUFFER_SIZE, &sum);
            for(int i = 0; i< sum; i++){
                printf("%c",ptx[i]);
            }
            printf("\n");
            free(ptx);
            */


            // tets content length as number
            /*
            int number = getContentLengthAsNumber(buffer,BUFFER_SIZE);
            printf("%d\n",number);
            */


            // TEST THE findBoundaryString function !!!
            /*
            int n;
            char* ptr = findBoundaryString(buffer,BUFFER_SIZE,&n);
            printf("DU HUAN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            
            for(int i = 0; i<n; i++){
                printf("%c",ptr[i]);
            }
            printf("\n");
            free(ptr);
            */


            // TEST gen Start BD String here !!!
            /*
            printf("PRITNING GENRATED BD STRING GUYS :)\n");
            int s;
            char* ptr = genStartingBD_STRING(buffer,BUFFER_SIZE,&s);
            pChars(ptr,s);
            free(ptr);
            */

            // TEST END BD STRING INDEX FUNCTION !!!!
            /*
            int num = searchForEndBoundaryString(buffer,BUFFER_SIZE);
            for(int i = num; i<STATUS; i++){
                printf("%c",buffer[i]);
            }
            printf("\n");

            */

            // TEST THE BEST CASE MODE
            BEST_CASE_MODE(buffer,BUFFER_SIZE);


            // IK brother its hard but pls try post handling here
            //postHandling(buffer,BUFFER_SIZE,&STATUS);


            //after all is load into memory
            send(foo,http_response,strlen(http_response),0);
            printf(" \n");
        }

        printf("HTTP RESPONSE WAS SEND\n\n");


        close(foo);
        memset(buffer,0,sizeof(buffer));

    }
    
    close(foo);
    free(LARGE_DATA_BUFFER);
    return 0;
}
