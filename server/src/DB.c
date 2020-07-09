#include "DB.h"

int ConnectToDB()
{
	if(isConnected)
		return RET_OK;
	connection = mysql_init(NULL);

	if(connection == NULL) 
	{
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		return RET_ERROR;
	}

	if(mysql_real_connect(connection, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) 
	{
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		mysql_close(connection);
	  	return RET_ERROR;
	}
	isConnected = 1;
	return RET_OK;
}

int InsertUserValue(User* user)
{
	ret_t ret = RET_OK;
	char* query = (char*)malloc(MAXBUFFERSIZE*sizeof(char));
	strcpy(query, "INSERT INTO Users(Name, Password) VALUES(\"");
	strcat(query, user->login);
	strcat(query, "\",\"");
	strcat(query, user->password);
	strcat(query, "\")");
	if(mysql_query(connection, query))
	{
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		ret = RET_ERROR;
	}
	free(query);
	return ret;
}

UserListNode* GetAllUsers()
{
	if(mysql_query(connection, "SELECT * FROM Users")) 
	{
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		return NULL;
	}
	
	MYSQL_RES *result = mysql_store_result(connection);
  	if(result == NULL) 
		return NULL;

	int numRows = mysql_num_rows(result);

	MYSQL_ROW row;

	UserListNode* head = NULL; 

	while((row = mysql_fetch_row(result))) 
	{
		User* user = (User *)malloc(sizeof(User)); 
		user->id = atoi(row[0]);
		strcpy(user->login, row[1] ? row[1] : "NULL");
		strcpy(user->password, row[2] ? row[2] : "NULL");
		head = Add(head, user);
	}

	mysql_free_result(result);

	head = Reverse(head);
	return head;
}

User* GetUserByName(const char* username)
{
	char* query = (char*)malloc(MAXBUFFERSIZE*sizeof(char));
	strcpy(query, "SELECT * FROM Users WHERE Name=\"");
	strcat(query, username);
	strcat(query, "\"");

	if(mysql_query(connection, query)) 
	{
		free(query);
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		return NULL;
	}

	free(query);

	MYSQL_RES *result = mysql_store_result(connection);
	
  	if(result == NULL) 
		return NULL;

	MYSQL_ROW row;
	User* user = NULL;

	if((row = mysql_fetch_row(result)))
	{
		user = (User *)malloc(sizeof(User));
		user->id = atoi(row[0]);
		strcpy(user->login, row[1] ? row[1] : "NULL");
		strcpy(user->password, row[2] ? row[2] : "NULL");
	}

	mysql_free_result(result);
	return user;
}

void CloseDB()
{
	mysql_close(connection);
}