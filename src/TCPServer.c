#include "TCPServer.h"
#include <pthread.h>
#include <syslog.h>
#include <string.h>

void *ConnectionHandler(void *ptr);

int StartTCPServer(int port)
{
	int server_fd; 
    struct sockaddr_in address; 
    int opt = 1; 
    openlog("server",LOG_PID,LOG_USER); 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
    	syslog(LOG_ERR,"Socket failed");
        return -1;
    } 

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        return -1;
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port); 
       
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
    	syslog(LOG_ERR,"Bind failed");
        return -1;
    } 
    if (listen(server_fd, MAXCLIENT) < 0) 
    { 
    	syslog(LOG_ERR,"Listen failed");
        return -1;
    } 
    syslog(LOG_INFO,"Server listening");
    return server_fd;
}

int Accept(int server_fd)
{
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	socket_descr_t * socketDescr = (socket_descr_t *)malloc(sizeof(socket_descr_t));

	socketDescr->socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen);
	if (socketDescr->socket <= 0)
	{
		free(socketDescr);
		return 0;
	}
	else
	{
		socketDescr->ip = inet_ntoa(address.sin_addr);
		syslog(LOG_INFO,"Client has been accepted, ip %s\n", socketDescr->ip);
		pthread_t thread;
		pthread_create(&thread, 0, ConnectionHandler, (void *)socketDescr);
		pthread_detach(thread);
		return 1;
	}
}

void *ConnectionHandler(void *ptr)
{
	int len;
	socket_descr_t *socketDescr;
	long addr = 0;

	if (!ptr) 
		pthread_exit(0); 
	
	syslog(LOG_INFO,"threadCreated");
	socketDescr = (socket_descr_t *)ptr;

	while(1)
	{
		RunThreadApp(socketDescr->ip, socketDescr->socket);
	}

	close(socketDescr->socket);
	free(socketDescr);
	pthread_exit(0);
}