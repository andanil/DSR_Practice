#include "TCPConnection.h"

Message message;
Data data;

int Send(int socket, Message* mess)
{
	if(socket < 0) 
	{
		return 0;
	}
	if(send(socket, mess, sizeof(*mess), 0) < 0)
	{
		return 0;
	}
	return 1;
}

Message* Read(int socket)
{
	if( recv(socket, &message, sizeof(Message), 0) < 0)
  	{
		return NULL;
  	}
  	return &message;
}

int SendData(int socket, Data* mess)
{
	if(socket < 0) 
		return 0;
	if(send(socket, mess, sizeof(*mess), 0) < 0)
		return 0;
	return 1;
}

Data* ReadData(int socket)
{
	if( recv(socket, &data, sizeof(Data), 0) < 0)
  	{
		return NULL;
  	}
  	return &data;
}