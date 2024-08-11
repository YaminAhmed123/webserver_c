// static buffers for frontend
#include <endian.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

char HTML_BUFFER[1024];
char CSS_BUFFER[1024];
char JS_BUFFER[1024];

char HEADER_HTML[256];
char HEADER_CSS[256];
char HEADER_JS[256];


void genHEADER_HTML()
{
    memset(HEADER_HTML,0,sizeof(HEADER_HTML));

    sprintf(HEADER_HTML, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/html\r\n\r\n",(int)strlen(HTML_BUFFER));
}

void genHEADER_CSS()
{
    memset(HEADER_CSS,0,sizeof(HEADER_CSS));

    sprintf(HEADER_CSS, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/css\r\n\r\n", (int)strlen(CSS_BUFFER));
}

void genHEADER_JS()
{
    memset(HEADER_JS,0,sizeof(HEADER_JS));

    sprintf(HEADER_JS, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/javascript\r\n\r\n", (int)strlen(JS_BUFFER));
}






void SEND_HTML(int fd)
{
    send(fd, HEADER_HTML, strlen(HEADER_HTML),0);
    send(fd, HTML_BUFFER, strlen(HTML_BUFFER),0);
}

void SEND_CSS(int fd)
{
    send(fd, HEADER_CSS, strlen(HEADER_CSS),0);
    send(fd,CSS_BUFFER,strlen(CSS_BUFFER),0);
}

void SEND_JS(int fd)
{
    send(fd,HEADER_JS,strlen(HEADER_JS),0);
    send(fd,JS_BUFFER,strlen(JS_BUFFER),0);
}




void POST_LISTEN()
{

}


char CHECK_REQUEST(char* BUFFER)
{
    char tempBuffer[256];
    int lastIndex;

    char* HTML = "GET / HTTP/1.1";
    char* CSS = "GET /index.css HTTP/1.1";
    char* JS = "GET /index.js HTTP/1.1";

    for(int i = 0; i<100;++i)
    {
        if(BUFFER[i] == '\r')
        {
            lastIndex = i;
            break;
        } else {
        tempBuffer[i] = BUFFER[i];
        }
    }

    tempBuffer[lastIndex] = '\0';

    if(strcmp(tempBuffer,HTML)==0){ return 'H'; }
    if(strcmp(tempBuffer,CSS)==0){ return 'C'; }
    if(strcmp(tempBuffer,JS)==0){ return 'J'; }

    //check if it is POST request
    char postCheck[5];
    for(int i = 0; i<4; i++)
    {
        postCheck[i] = tempBuffer[i];
    }
    postCheck[4] = '\0';
    if(strcmp(postCheck,"POST")==0) {return 'P';}

    return -1;
}

