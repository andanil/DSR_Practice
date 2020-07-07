#include "ServerController.h"

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

	User* userDB = GetUserByName(newUser->login);
	if(userDB != NULL)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Unavailable user name");

		char message[MAXMESSAGESIZE];
		strcpy(message, "User with name ");
		strcat(message, userDB->login);
		strcat(message, " already exists");
		free(userDB);

		if(!Send(socket, JsonSendErrorMessage(ERROR, message)))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	
	if(!InsertUserValue(newUser))
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Insert user failed");

		if(!Send(socket, JsonSendErrorMessage(ERROR, "Cannot register user")))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}

	User* regUser = GetUserByName(newUser->login);
	if(regUser != NULL)
	{
		userID = regUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Registration completed successfully");

		if(!Send(socket, JsonSendUser(SUCCESS, regUser)))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");

		free(regUser);
		return;
	}

	Log(LOGGERFILENAME, "CONTR_ERROR", "Registration failed");

	if(!Send(socket, JsonSendErrorMessage(ERROR, "Cannot find registered user")))
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

	User* logUser = GetUserByName(client->login);
	if(logUser == NULL)
	{
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in failed");

		char name[DATASIZE];
		char message[MAXMESSAGESIZE];
		strcpy(name, client->login);
		strcpy(message, "No user with name ");
		strcat(message, name);

		if(!Send(socket, JsonSendErrorMessage(ERROR, message)))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}
	if(strcmp(client->password, logUser->password) == 0)
	{
		userID = logUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in completed successfully");
		
		if(!Send(socket, JsonSendUser(SUCCESS, logUser)))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");

		free(logUser);
		return;
	}
	free(logUser);
	Log(LOGGERFILENAME, "CONTR_INFO", "Log in failed");

	if(!Send(socket, JsonSendErrorMessage(ERROR, "Incorrect password")))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	return;
}

void GetClientData(int socket, Data* data)
{
	if(!CheckUserId(data->userId, socket))
		return;

	if(!Send(socket, JsonSendSuccessMessage(SUCCESS)))
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	Log(LOGGERFILENAME, "CONTR_INFO", "Get data from user successfully");

	JsonWriteGPSInfoWithId(JSONFILENAME, data);
}

int CheckCorrectness(int socket, User* user)
{
	if(!(user->login != NULL && user->login != "" && user->password != NULL && user->password != ""))
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Incorrect user info");
		if(!Send(socket, JsonSendErrorMessage(ERROR, "Incorrect user info")))
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

		if(!Send(socket, JsonSendErrorMessage(ERROR, "Incorrect user id. You hasn't logged in yet")))
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return 0;
	}
	return 1;
}