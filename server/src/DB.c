#include "DB.h"

int ConnectToDB()
{
	if(isConnected)
		return 1;
	connection = mysql_init(NULL);

	if(connection == NULL) 
	{
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		return 0;
	}

	if(mysql_real_connect(connection, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) 
	{
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		mysql_close(connection);
	  	return 0;
	}
	isConnected = 1;
	return 1;
}

int InsertUserValue(User* user)
{
	char* query = (char*)malloc(MAXBUFFERSIZE*sizeof(char));
	strcpy(query, "INSERT INTO Users(Name, Password) VALUES(\"");
	strcat(query, user->name);
	strcat(query, "\",\"");
	strcat(query, user->password);
	strcat(query, "\")");
	if(mysql_query(connection, query))
	{
		free(query);
		Log(LOGGERFILENAME, "SQL_ERROR", mysql_error(connection));
		return 0;
	}
	free(query);
	return 1;
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
		strcpy(user->name, row[1] ? row[1] : "NULL");
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
		strcpy(user->name, row[1] ? row[1] : "NULL");
		strcpy(user->password, row[2] ? row[2] : "NULL");
	}

	mysql_free_result(result);
	return user;
}

void CloseDB()
{
	mysql_close(connection);
}