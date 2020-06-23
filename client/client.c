#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "../inc/TCPClient.h"
   
int main(int argc, char const *argv[]) 
{ 
    if(argc < 2) 
    {
        printf("Arguments have been expected\n"); 
        return 0;
    }
    printf("TCP client initialization\n"); 
    int socket = InitTCPClient(); 
    if(socket < 0)
        printf("Socket creation error \n"); 

    printf("Connecting to server\n"); 
    if(!Connect(socket, 8080, argv[1]))
    {
        printf("Socket connection error \n"); 
        return 0;
    }

    message_t * message = (message_t *)malloc(sizeof(message_t));
    int run = 1;
    while(run)
    {
        printf("Choose command:\n"); 
        printf("1.Send username\n"); 
        printf("2.Send password\n"); 
        printf("3.Send command\n"); 
        printf("4.Exit\n"); 

        int command;
        if(scanf("%d", &command)) 
        {
            switch(command)
            {
                case 1:
                {
                    printf("Username:\n");
                    char name[MAXPACKETSIZE];
                    if(!scanf("%s", name)) 
                    {
                        printf("Incorrect input\n");   
                        break;
                    }
                    strcpy(message->data, name);
                    message->dataType = USERNAME;
                    Send(socket, message);
                    break;
                }
                case 2:
                {
                    printf("Password:\n");
                    char pass[MAXPACKETSIZE];
                    if(!scanf("%s", pass)) 
                    {
                        printf("Incorrect input\n");   
                        break;
                    }
                    strcpy(message->data, pass);
                    message->dataType = PASSWORD;
                    Send(socket, message);
                    break;
                }
                case 3:
                {
                    printf("Command:\n");
                    char com[MAXPACKETSIZE];
                    if(!scanf("%s", com)) 
                    {
                        printf("Incorrect input\n");   
                        break;
                    }
                    strcpy(message->data, com);
                    message->dataType = COMMAND;
                    Send(socket, message);
                    break;
                }
                case 4:
                {
                    run = 0;
                    break;
                }
                default:
                    printf("Unknown command\n");
            }
        }
    }
    
    close(socket);
    free(message);
    return 0; 
} 