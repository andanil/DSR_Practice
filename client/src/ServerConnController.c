#include "ServerConnController.h"

Message message;
extern User user;

const char* Register(int socket, const char* name, const char* password, const char* confPassword)
{
	if(strcmp(password, confPassword) != 0)
		return "Password mismatch";
	strcpy(user.name, name);
	strcpy(user.password, password);
	message.user = user;
	message.messageType = SINGIN;
	if(!Send(socket, &message))
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return "Cannot send data";
	}
	message = *Read(socket);
	if(&message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return "Cannot receive data";
	}
	if(message.messageType == ERROR)
		return message.user.name;
	user = message.user;
	return "Success";	
}

const char* LogIn(int socket, const char* name, const char* password)
{
	strcpy(user.name, name);
	strcpy(user.password, password);
	message.user = user;
	message.messageType = LOGIN;
	if(!Send(socket, &message))
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return "Cannot send data";
	}

	message = *Read(socket);
	if(&message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return "Cannot receive data";
	}
	if(message.messageType == ERROR)
		return message.user.name;
	user = message.user;
	return "Success";	
}

const char* SendData(int socket)
{
	message.user = user;
	message.messageType = SENDDATA;
	if(!Send(socket, &message))
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return "Cannot send data";
	}

	message = *Read(socket);
	if(&message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return "Cannot receive data";
	}
	if(message.messageType == ERROR)
		return message.user.name;
	return "Success";	
}