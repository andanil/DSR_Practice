#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include "../inc/TCPServer.h"

int main(int argc, char const *argv[]) 
{ 
    int server_fd = StartTCPServer(8080);
    if(server_fd < 0)
    {
        printf("Can't start server\n");
        return 1;
    }
    
    while(1)
    {
        if(!Accept(server_fd))
            printf("Accept failed\n");
    }
    close(server_fd);
    return 0; 
} 