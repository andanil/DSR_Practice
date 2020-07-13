#include "ServerConnController.h"

extern User user;

const char* Login(int socket);

const char* Register(int socket, const char* login, const char* password, const char* confPassword)
{
	if(strcmp(password, confPassword) != 0)
		return "Password mismatch";
	strcpy(user.login, login);
	strcpy(user.password, password);
	if(Send(socket, JsonSendUser(SINGIN, &user)) == RET_ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return "Cannot send data";
	}
	const char* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return "Cannot receive data";
	}
	if(JsonGetMessageType(message) == ERROR)
		return JsonGetErrorMessage(message);

	user = *JsonGetUser(message);
	if(&user == NULL)
	{	
        Log(LOGGERFILENAME, "JSON_ERROR", "Parse user failed");
		return "Cannot receive user info";
	}
	
	return "Success";	
}

const char* LogIn(int socket, const char* name, const char* password)
{
	strcpy(user.login, name);
	strcpy(user.password, password);
	return Login(socket);	
}

const char* AutoLogIn(int socket)
{
	if(!ReadUserData(&user))
		return "Read user info error";
	return Login(socket);
}

const char* LogOut(int socket)
{
	if(Send(socket, JsonSendUser(LOGOUT, &user)) == RET_ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return "Cannot send data";
	}

	const char* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return "Cannot receive data";
	}
	if(JsonGetMessageType(message) == ERROR)
		return JsonGetErrorMessage(message);

	user.id = -1;
	return "Success";
}

int SendUserData(int socket, GPSInfo* data)
{
	if(Send(socket, JsonSendGPSInfo(DATA, user.id, data)) == RET_ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send data failed");
		return RET_ERROR;
	}

	const char* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return RET_ERROR;
	}
	if(JsonGetMessageType(message) == ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", JsonGetErrorMessage(message));
		return RET_ERROR;
	}
	
	return RET_OK;	
}

const char* Login(int socket)
{
	if(Send(socket, JsonSendUser(LOGIN, &user)) == RET_ERROR)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return "Cannot send data";
	}

	const char* message = Read(socket);
	if(message == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read failed");
		return "Cannot receive data";
	}
	if(JsonGetMessageType(message) == ERROR)
		return JsonGetErrorMessage(message);
	user = *JsonGetUser(message);
	if(&user == NULL)
	{	
        Log(LOGGERFILENAME, "JSON_ERROR", "Parse user failed");
		return "Cannot receive user info";
	}
	return "Success";
}