#include "ServerConnController.h"

Message message;
extern User user;

const char* Login(int socket);

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
	return Login(socket);	
}

const char* AutoLogIn(int socket)
{
	if(!ReadUserData(&user))
		return "Read user info error";
	message.user = user;
	message.messageType = LOGIN;
	return Login(socket);
}

int SendUserData(int socket, GPSInfo* data)
{
	message.user = user;
	message.messageType = SENDDATA;
	if(!Send(socket, &message))
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return 0;
	}

	message = *Read(socket);
	if(&message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return 0;
	}
	if(message.messageType == ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", message.user.name);
		return 0;
	}

	Data* dataMessage = (Data*)malloc(sizeof(Data));
	dataMessage->userId = user.id;
	dataMessage->data = *data;
	if(!SendData(socket, dataMessage))
	{
		free(dataMessage);
		Log(LOGGERFILENAME, "TCP_ERROR", "Send data failed");
		return 0;
	}
	free(dataMessage);

	message = *Read(socket);
	if(&message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return 0;
	}
	if(message.messageType == ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", message.user.name);
		return 0;
	}
	
	return 1;	
}

const char* Login(int socket)
{
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