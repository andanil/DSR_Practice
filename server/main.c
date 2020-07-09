#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include "TCPServer.h"

int main(int argc, char const *argv[]) 
{ 
    int server = StartTCPServer(8080);
    if(server < 0)
    {
        printf("Can't start server\n");
        return 1;
    }
    
    while(1)
    {
        if(Accept(server) == RET_ERROR)
            printf("Accept failed\n");
    }
    close(server);
    return 0; 
} 