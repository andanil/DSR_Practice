#include "ServerApp.h"

void RunThreadApp(const char* ip, int socket)
{
	Message* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return;
	}
	switch(message->dataType)
	{
		case USERNAME:
		{
			printf("IP address: %s, username: %s\n", ip, message->data);
			break;
		}
		case PASSWORD:
		{
			printf("IP address: %s, password: %s\n", ip, message->data);
			break;
		}
		case COMMAND:
		{
			printf("IP address: %s, command: %s\n", ip, message->data);
			break;
		}
	}
}