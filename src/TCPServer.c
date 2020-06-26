#include "TCPServer.h"
#include <pthread.h>
#include <syslog.h>
#include <string.h>

void *ConnectionHandler(void *ptr);
int IsAvailableClient(int socket);

int StartTCPServer(int port)
{
	int server; 
    struct sockaddr_in address; 
    int opt = 1; 
    openlog("server",LOG_PID,LOG_USER); 

    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
    	syslog(LOG_ERR,"Socket failed");
    	closelog();
        return -1;
    } 
    int retCode = NO_ERROR;
    do
    {
    	retCode = setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    	if(retCode)
    		break;
    	
    	address.sin_family = AF_INET; 
	    address.sin_addr.s_addr = INADDR_ANY; 
	    address.sin_port = htons(port); 
    	
    	retCode = bind(server, (struct sockaddr *)&address, sizeof(address));
    	if(retCode)
    	{
    		syslog(LOG_ERR,"Bind failed");
    		break;
    	}
    	retCode = listen(server, MAXCLIENT);
    	if(retCode)
    	{
    		syslog(LOG_ERR,"Listen failed");
    		break;
    	}
    }
    while(0);

    if (retCode != NO_ERROR)
	{
		closelog();
	  	return -1;
	}
    syslog(LOG_INFO,"Server listening");
    closelog();
    return server;
}

int Accept(int server)
{
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	socket_descr_t * socketDescr = (socket_descr_t *)malloc(sizeof(socket_descr_t));
	
	openlog("server",LOG_PID,LOG_USER); 
	socketDescr->socket = accept(server, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen);
	if (socketDescr->socket <= 0)
	{
		syslog(LOG_ERR,"Accept failed\n");
		closelog();
		free(socketDescr);
		return 0;
	}
	else
	{
		socketDescr->ip = inet_ntoa(address.sin_addr);
		syslog(LOG_INFO,"Client has been accepted, ip %s\n", socketDescr->ip);

		int running = 1;
		while(running)
		{
			RunThreadApp(socketDescr->ip, socketDescr->socket);
			running = IsAvailableClient(socketDescr->socket);
		}
		syslog(LOG_INFO,"Client is not available, ip %s\n", socketDescr->ip);
		closelog();
		close(socketDescr->socket);
		free(socketDescr);

		/*pthread_t thread;
		pthread_create(&thread, 0, ConnectionHandler, (void *)socketDescr);
		pthread_detach(thread);*/
		return 1;
	}
}

void *ConnectionHandler(void *ptr)
{
	char buffer;
	int len;
	socket_descr_t *socketDescr;
	long addr = 0;

	if (!ptr) 
		pthread_exit(0); 
	
	syslog(LOG_INFO,"threadCreated");
	socketDescr = (socket_descr_t *)ptr;
	int running = 1;
	while(running)
	{
		RunThreadApp(socketDescr->ip, socketDescr->socket);
		running = IsAvailableClient(socketDescr->socket);
	}

	close(socketDescr->socket);
	free(socketDescr);
	pthread_exit(0);
}

int IsAvailableClient(int socket)
{
	char buffer;
	int result = recv(socket, &buffer, 1, MSG_PEEK);
	if (result > 0)
		return 1;
	return 0;
}