#include "ServerApp.h"

void RunThreadApp(const char* ip, int socket)
{
	Message* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return;
	}
	switch(message->messageType)
	{
		case SINGIN:
		{
			RegisterClient(socket, &message->user);
			break;
		}
		case LOGIN:
		{
			LogIn(socket, &message->user);
			break;
		}
		case SENDDATA:
		{
			GetClientData(socket, &message->user);
			break;
		}
	}
}