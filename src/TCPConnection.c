#include "TCPConnection.h"

char message[MAXMESSAGESIZE];

int Send(int socket, const char* mess)
{
	if(socket < 0) 
		return RET_ERROR;

	if(send(socket, mess, MAXMESSAGESIZE, 0) < 0)
		return RET_ERROR;

	return RET_OK;
}

const char* Read(int socket)
{
	if( recv(socket, message, MAXMESSAGESIZE, 0) < 0)
  	{
		return NULL;
  	}
  	return message;
}