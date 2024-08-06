// static buffers for frontend
#include <endian.h>
#include <string.h>
#include <stdio.h>

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

    sprintf(HEADER_JS, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/js\r\n\r\n", (int)strlen(JS_BUFFER));
}

