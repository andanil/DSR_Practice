#include "ServerApp.h"

void RunThreadApp(const char* ip, int socket)
{
	message_t* message = Read(socket);
	if(message == NULL)
		return;
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