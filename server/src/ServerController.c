#include "ServerController.h"

static Message message;
static userID = -1;

int CheckCorrectness(int socket, User* user);

void RegisterClient(int socket, User* user)
{
	if(!CheckCorrectness(socket, user))
		return;

	User* userDB = GetUserByName(user->name);
	if(userDB != NULL)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Unavailable user name");
		message.messageType = ERROR;
		strcpy(message.user.name, "User with name ");
		strcat(message.user.name, user->name);
		strcat(message.user.name, "already exists");

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	if(!InsertUserValue(user))
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Insert user failed");
		message.messageType = ERROR;
		strcpy(message.user.name, "Cannot register user");

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	User* regUser = GetUserByName(user->name);
	if(regUser != NULL)
	{
		userID = regUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Registration completed successfully");
		message.messageType = SUCCESS;
		message.user = *regUser;
		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	Log(LOGGERFILENAME, "CONTR_ERROR", "Registration failed");
	message.messageType = ERROR;
	strcpy(message.user.name, "Cannot find registered user");

	if(!Send(socket, &message))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	return;
}

void LogIn(int socket, User* user)
{
	if(!CheckCorrectness(socket, user))
		return;

	User* logUser = GetUserByName(user->name);
	if(logUser == NULL)
	{
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in failed");
		message.messageType = ERROR;
		strcpy(message.user.name, "No user with name ");
		strcat(message.user.name, user->name);

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	if(strcmp(user->password, logUser->password) == 0)
	{
		userID = logUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in completed successfully");
		message.messageType = SUCCESS;
		message.user = *logUser;
		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	Log(LOGGERFILENAME, "CONTR_INFO", "Log in failed");
	message.messageType = ERROR;
	strcpy(message.user.name, "Incorrect password");

	if(!Send(socket, &message))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	return;
}

void GetClientData(int socket, User* user)
{
	if(userID != user->id)
	{
		Log(LOGGERFILENAME, "CONTR_INFO", "Get client data failed, incorrect id");
		message.messageType = ERROR;
		strcpy(message.user.name, "Incorrect user id. You hasn't logged in yet");

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}

	message.messageType = SUCCESS;
	message.user = NULL;
	if(!Send(socket, &message))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	
	Log(LOGGERFILENAME, "CONTR_INFO", "Waiting data from user");
}

int CheckCorrectness(int socket, User* user)
{
	if(!(user->name != NULL && user->name != "" && user->password != NULL && user->password != ""))
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Incorrect user info");
		message.messageType = ERROR;
		message.user = *user;
		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return 0;
	}
	return 1;
}