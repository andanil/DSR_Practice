#include "ServerApp.h"

void RunThreadApp(const char* ip, int socket)
{
	const char* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return;
	}
	switch(JsonGetMessageType(message))
	{
		case SINGIN:
		{
			RegisterClient(socket, message);
			break;
		}
		case LOGIN:
		{
			LogIn(socket, message);
			break;
		}
		case DATA:
		{
			GetClientData(socket, message);
			break;
		}
		case LOGOUT:
		{
			LogOut(socket, message);
			break;
		}
	}
}