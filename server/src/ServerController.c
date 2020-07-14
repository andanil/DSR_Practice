#include "ServerController.h"

static int userID = -1;

int CheckCorrectness(int socket, User* user);

void RegisterClient(int socket, const char* message)
{
	char sendMessage[MAXMESSAGESIZE];
	char errorMessage[ERRORMESSAGESIZE];

	ret_t ret = RET_OK;
    do
    {
    	ret = ConnectToDB();
    	if(ret == RET_ERROR)
		{
			strcpy(errorMessage, "Cannot connect to database");
    		strcpy(sendMessage, "Cannot register user");
			break; 
		}

    	User* newUser = JsonGetUser(message);
    	if(newUser == NULL)
    	{
    		strcpy(errorMessage, "Parse user failed");
    		strcpy(sendMessage, "Cannot get user data");
			ret = RET_ERROR;
			break; 
    	}
    	ret = CheckCorrectness(socket, newUser);
		if(ret == RET_ERROR)
		{
			strcpy(errorMessage, "Incorrect user info");
    		strcpy(sendMessage, "Incorrect user info");
			break; 
		}

		User* userDB = GetUserByName(newUser->login);
		if(userDB != NULL)
		{
			strcpy(errorMessage, "Unavailable user name");
			
			strcpy(sendMessage, "User with name ");
			strcat(sendMessage, userDB->login);
			strcat(sendMessage, " already exists");

			free(userDB);
			ret = RET_ERROR;
			break;
		}
		
		ret = InsertUserValue(newUser);
		if(ret == RET_ERROR)
		{
			strcpy(errorMessage, "Insert user failed");
			strcpy(sendMessage, "Cannot register user");
			ret = RET_ERROR;
			break;
		}

		User* regUser = GetUserByName(newUser->login);
		if(regUser == NULL)
		{
			strcpy(errorMessage, "Registration failed");
			strcpy(sendMessage, "Cannot find registered user");
			ret = RET_ERROR;
			break;
		}

		userID = regUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Registration completed successfully");

		if(Send(socket, JsonSendUser(SUCCESS, regUser)) == RET_ERROR)
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");

		free(regUser);
    }
    while(0);

    if (ret != RET_OK)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", errorMessage);

		if(Send(socket, JsonSendErrorMessage(ERROR, sendMessage)) == RET_ERROR)
				Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	}
}

void LogIn(int socket, const char* message)
{
	char sendMessage[MAXMESSAGESIZE];
	char errorMessage[ERRORMESSAGESIZE];
	ret_t ret = RET_OK;
    do
    {
    	ret = ConnectToDB();
    	if(ret == RET_ERROR)
		{
			strcpy(errorMessage, "Cannot connect to database");
    		strcpy(sendMessage, "Cannot register user");
			break; 
		}

    	User* client = JsonGetUser(message);
    	if(client == NULL)
    	{
    		strcpy(errorMessage, "Parse user failed");
    		strcpy(sendMessage, "Cannot get user data");
			ret = RET_ERROR;
			break; 
    	}
    	ret = CheckCorrectness(socket, client);
		if(ret == RET_ERROR)
		{
			strcpy(errorMessage, "Incorrect user info");
    		strcpy(sendMessage, "Incorrect user info");
			break; 
		}

		User* logUser = GetUserByName(client->login);
		if(logUser == NULL)
		{
			char name[DATASIZE];
			strcpy(name, client->login);
			strcpy(sendMessage, "No user with name ");
			strcat(sendMessage, name);
			strcpy(errorMessage, "Log in failed");

			ret = RET_ERROR;
			break;
		}
		
		if(strcmp(client->password, logUser->password) != 0)
		{
			strcpy(sendMessage, "Incorrect password");
			free(logUser);
			strcpy(errorMessage, "Log in failed");
			ret = RET_ERROR;
			break;
		}

		userID = logUser->id;
		Log(LOGGERFILENAME, "CONTR_INFO", "Log in completed successfully");
		
		if(Send(socket, JsonSendUser(SUCCESS, logUser)) == RET_ERROR)
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");

		free(logUser);
    }
    while(0);

    if (ret != RET_OK)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", errorMessage);

		if(Send(socket, JsonSendErrorMessage(ERROR, sendMessage)) == RET_ERROR)
				Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	}
}

void GetClientData(int socket, const char* message)
{
	Data* data = JsonGetData(message);
	if(data == NULL)
	{
		Log(LOGGERFILENAME, "JSON_ERROR", "Parse data failed");

		if(Send(socket, JsonSendErrorMessage(ERROR, "Cannot get user data")) == RET_ERROR)
				Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return; 
	}

	if(userID != data->userId)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", "Get client data failed, incorrect id");

		if(Send(socket, JsonSendErrorMessage(ERROR, "Incorrect user id. You hasn't logged in yet")) == RET_ERROR)
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
		return;
	}

	if(Send(socket, JsonSendSuccessMessage(SUCCESS)) == RET_ERROR)
		Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	Log(LOGGERFILENAME, "CONTR_INFO", "Get data from user successfully");

	if(InsertGPSData(data) == RET_ERROR)
		Log(LOGGERFILENAME, "CONTR_INFO", "Save data to DB failed");
	else
		Log(LOGGERFILENAME, "CONTR_INFO", "Save data to DB successfully");
}

void LogOut(int socket, const char* message)
{
	char sendMessage[MAXMESSAGESIZE];
	char errorMessage[ERRORMESSAGESIZE];
	ret_t ret = RET_OK;
    do
    {
    	User* client = JsonGetUser(message);
    	if(client == NULL)
    	{
    		strcpy(errorMessage, "Parse user failed");
    		strcpy(sendMessage, "Cannot get user data");
			ret = RET_ERROR;
			break; 
    	}
    	ret = CheckCorrectness(socket, client);
		if(ret == RET_ERROR)
		{
			strcpy(errorMessage, "Incorrect user info");
    		strcpy(sendMessage, "Incorrect user info");
			break; 
		}

		if(userID != client->id)
		{
			strcpy(errorMessage, "Incorrect client's id");
    		strcpy(sendMessage, "Incorrect user id. You hasn't logged in");
			break; 
		}

		userID = -1;
		Log(LOGGERFILENAME, "CONTR_INFO", "Log out completed successfully");
		
		if(Send(socket, JsonSendSuccessMessage(SUCCESS)) == RET_ERROR)
			Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
    }
    while(0);

    if (ret != RET_OK)
	{
		Log(LOGGERFILENAME, "CONTR_ERROR", errorMessage);

		if(Send(socket, JsonSendErrorMessage(ERROR, sendMessage)) == RET_ERROR)
				Log(LOGGERFILENAME, "TCP_ERROR", "Send failed");
	}
}

int CheckCorrectness(int socket, User* user)
{
	ret_t ret = RET_OK;
	if(!(user->login != NULL && user->login != "" && user->password != NULL && user->password != ""))
	{
		ret = RET_ERROR;
	}
	return ret;
}

UserListNode* GetUsers()
{
	if(ConnectToDB() == RET_ERROR)
	{
		Log(LOGGERFILENAME, "DB_ERROR", "Cannot connect to database");
		return NULL; 
	}

	UserListNode* users = GetAllUsers();
	if(users == NULL)
		Log(LOGGERFILENAME, "DB_ERROR", "Cannot get users");

	return users;
}

int DeleteUser(int id)
{
	char message[ERRORMESSAGESIZE];
	ret_t ret = RET_OK;
    do
    {
    	ret = ConnectToDB();
    	if(ret == RET_ERROR)
		{
			strcpy(message, "Cannot connect to database");
			break; 
		}

		ret = DeleteUserById(id);
		if(ret == RET_ERROR)
		{
			strcpy(message, "Cannot delete user");
			break;
		}
    }
    while(0);

    if (ret != RET_OK)
		Log(LOGGERFILENAME, "DB_ERROR", message);

	return ret;
}