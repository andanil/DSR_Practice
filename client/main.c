#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "TCPClient.h"
   
int main(int argc, char const *argv[]) 
{ 
    if(argc < 2) 
    {
        printf("Arguments have been expected\n"); 
        return 0;
    }
    Log(LOGGERFILENAME, "TCP_INFO", "TCP client initialization");
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
   
    Message * message = (Message *)malloc(sizeof(Message));
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
                    char name[DATASIZE];
                    if(!scanf("%s", name)) 
                    {
                        printf("Incorrect input\n");   
                        break;
                    }
                    //strcpy(message->user.name, name);
                    //message->messageType = USERNAME;
                    Send(socket, message);
                    break;
                }
                case 2:
                {
                    printf("Password:\n");
                    char pass[DATASIZE];
                    if(!scanf("%s", pass)) 
                    {
                        printf("Incorrect input\n");   
                        break;
                    }
                    //strcpy(message->user.name, pass);
                    //message->messageType = PASSWORD;
                    Send(socket, message);
                    break;
                }
                case 3:
                {
                    printf("Command:\n");
                    char com[DATASIZE];
                    if(!scanf("%s", com)) 
                    {
                        printf("Incorrect input\n");   
                        break;
                    }
                    //strcpy(message->user.name, com);
                    //message->messageType = COMMAND;
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