#include "TCPServer.h"
#include <pthread.h>
#include <string.h>

void *ConnectionHandler(void *ptr);
int IsAvailableClient(int socket);
void LogMessageWithIP(const char* mess, const char* ip);

int StartTCPServer(int port)
{
	int server; 
    struct sockaddr_in address; 
    int opt = 1; 

    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
    	Log(LOGGERFILENAME, "TCP_ERROR", "Socket failed");
        return -1;
    } 
    int retCode = RET_OK;
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
    		Log(LOGGERFILENAME, "TCP_ERROR", "Bind failed");
    		break;
    	}
    	retCode = listen(server, MAXCLIENT);
    	if(retCode)
    	{
    		Log(LOGGERFILENAME, "TCP_ERROR", "Listen failed");
    		break;
    	}
    }
    while(0);

    if (retCode != RET_OK)
	{
	  	return -1;
	}
    Log(LOGGERFILENAME, "TCP_INFO", "Server listening");
    return server;
}

int Accept(int server)
{
	ret_t ret = RET_OK;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	SocketDescr* socketDescr = (SocketDescr*)malloc(sizeof(SocketDescr));
	
	socketDescr->socket = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (socketDescr->socket <= 0)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Accept failed");
		free(socketDescr);
		ret = RET_ERROR;
	}
	else
	{
		socketDescr->ip = inet_ntoa(address.sin_addr);
		LogMessageWithIP("Client has been accepted, ip ", socketDescr->ip);

		int running = IsAvailableClient(socketDescr->socket);
		while(running == RET_OK)
		{
			LogMessageWithIP("Client is available, ip ", socketDescr->ip);
			RunThreadApp(socketDescr->ip, socketDescr->socket);
			running = IsAvailableClient(socketDescr->socket);
		}

		LogMessageWithIP("Client is not available, ip ", socketDescr->ip);

		close(socketDescr->socket);
		free(socketDescr);

		/*pthread_t thread;
		pthread_create(&thread, 0, ConnectionHandler, (void *)socketDescr);
		pthread_detach(thread);*/
	}
	return ret;
}

void *ConnectionHandler(void *ptr)
{
	char buffer;
	int len;
	SocketDescr *socketDescr;
	long addr = 0;

	if (!ptr) 
		pthread_exit(0); 

	Log(LOGGERFILENAME, "TCP_INFO", "Thread created");
	socketDescr = (SocketDescr *)ptr;

	int running = IsAvailableClient(socketDescr->socket);
	while(running == RET_OK)
	{
		LogMessageWithIP("Client is available, ip ", socketDescr->ip);
		RunThreadApp(socketDescr->ip, socketDescr->socket);
		running = IsAvailableClient(socketDescr->socket);
	}
	LogMessageWithIP("Client is not available, ip ", socketDescr->ip);

	close(socketDescr->socket);
	free(socketDescr);
	pthread_exit(0);
}

int IsAvailableClient(int socket)
{
	ret_t ret = RET_ERROR;
	char buffer;
	int result = recv(socket, &buffer, 1, MSG_PEEK);
	if (result > 0)
		ret = RET_OK;
	return ret;
}

void LogMessageWithIP(const char* mess, const char* ip)
{
	char* message = (char*)malloc(DATASIZE*sizeof(char));
	strcpy(message, mess);
	strcat(message, ip);
	Log(LOGGERFILENAME, "TCP_INFO", message);
	free(message);
}