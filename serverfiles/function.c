// static buffers for frontend
#include <string.h>

char HTML_BUFFER[1024];
char CSS_BUFFER[1024];
char JS_BUFFER[1024];


char HTTP_RESPONSE[2048];


void genHTML_HEADER()
{

}

void genCSS_HEADER()
{

}

void genJS_HEADER()
{

}


void CONNECT_HTTP_RESPONSE_BUFFER(char* BUFFER, char type)
{
    memset(HTTP_RESPONSE,0,sizeof(HTTP_RESPONSE));
    HTTP_RESPONSE[2047] = '\0';
    
    switch(type)
    {
        case 'h': genHTML_HEADER();
        break;

        case 'c': genCSS_HEADER();
        break;

        case 'j': genJS_HEADER();
        break;
    }
}
