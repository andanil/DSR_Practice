#include "TCPConnection.h"

char message[MAXMESSAGESIZE];

int Send(int socket, const char* mess)
{
	if(socket < 0) 
	{
		return 0;
	}
	if(send(socket, mess, MAXMESSAGESIZE, 0) < 0)
	{
		return 0;
	}
	return 1;
}

const char* Read(int socket)
{
	if( recv(socket, message, MAXMESSAGESIZE, 0) < 0)
  	{
		return NULL;
  	}
  	return message;
}