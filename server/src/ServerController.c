#include "ServerController.h"

Message message;
static int userID = -1;

int CheckCorrectness(int socket, User* user);
int CheckUserId(int id, int socket);

void RegisterClient(int socket, User* newUser)
{
	if(!CheckCorrectness(socket, newUser))
		return;

	if(!ConnectToDB())
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Cannot connect to database");
		return;
	}

	User* userDB = GetUserByName(newUser->name);
	if(userDB != NULL)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Unavailable user name");
		message.messageType = ERROR;
		strcpy(message.user.name, "User with name ");
		strcat(message.user.name, userDB->name);
		strcat(message.user.name, " already exists");
		free(userDB);

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	
	if(!InsertUserValue(newUser))
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Insert user failed");
		message.messageType = ERROR;
		strcpy(message.user.name, "Cannot register user");

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}

	User* regUser = GetUserByName(newUser->name);
	if(regUser != NULL)
	{
		userID = regUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Registration completed successfully");
		message.messageType = SUCCESS;
		message.user = *regUser;
		free(regUser);

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

void LogIn(int socket, User* client)
{
	if(!CheckCorrectness(socket, client))
		return;

	if(!ConnectToDB())
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Cannot connect to database");
		return;
	}

	User* logUser = GetUserByName(client->name);
	if(logUser == NULL)
	{
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in failed");
		message.messageType = ERROR;
		char name[DATASIZE];
		strcpy(name, client->name);
		strcpy(message.user.name, "No user with name ");
		strcat(message.user.name, name);

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	if(strcmp(client->password, logUser->password) == 0)
	{
		userID = logUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in completed successfully");
		message.messageType = SUCCESS;
		message.user = *logUser;
		free(logUser);
		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	free(logUser);
	Log(LOGGERFILENAME, "CONTR_INFO", "Log in failed");
	message.messageType = ERROR;
	strcpy(message.user.name, "Incorrect password");

	if(!Send(socket, &message))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	return;
}

void GetClientData(int socket, User* client)
{
	if(!CheckUserId(client->id, socket))
		return;

	message.messageType = SUCCESS;
	if(!Send(socket, &message))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");

	Log(LOGGERFILENAME, "CONTR_INFO", "Waiting data from user");

	Data* userData = ReadData(socket);
	if(userData == NULL)
	{
		Log(LOGGERFILENAME, "TCP_ERROR", "Read data failed");
		return;
	}
	if(!CheckUserId(userData->userId, socket))
		return;

	message.messageType = SUCCESS;
	if(!Send(socket, &message))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	Log(LOGGERFILENAME, "CONTR_INFO", "Get data from user successfully");

	WriteDataToJsonFile(userData);
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

int CheckUserId(int id, int socket)
{
	if(userID != id)
	{
		Log(LOGGERFILENAME, "CONTR_INFO", "Get client data failed, incorrect id");
		message.messageType = ERROR;
		strcpy(message.user.name, "Incorrect user id. You hasn't logged in yet");

		if(!Send(socket, &message))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return 0;
	}
	return 1;
}