#include "FileAuthorization.h"

int WriteData(User* user)
{
	FILE *file = fopen(AUTHFILENAME, "w");
	if(file == NULL)
	{
		Log(LOGGERFILENAME, "AUTH_ERROR", "Open file error");
		return 0;
	}
	fprintf(file, "%s<===>%s", user->login, user->password);
	fclose(file);
	Log(LOGGERFILENAME, "AUTH_INFO", "Write new user info");
	return 1;
}

int ReadUserData(User* user)
{
	FILE* file = fopen(AUTHFILENAME, "r");
	if(file == NULL)
	{
		Log(LOGGERFILENAME, "AUTH_ERROR", "Open file error");
		return 0;
	}

	char* data = NULL;
	size_t len = 0;
    ssize_t read;
    if((read = getline(&data, &len, file)) == -1)
	{
		Log(LOGGERFILENAME, "AUTH_ERROR", "Incorrect info in file");
		return 0;
	}

	char* p = NULL;
	do
	{
	 	p = strtok(data, "<===>");
	 	if(!p)
	 		break;
	 	strcpy(user->login, p);
	 	p = strtok(NULL, "<===>");
	 	if(!p)
	 		break;
	 	strcpy(user->password, p);

	} while (0); 
	
    fclose(file);
    return 1;
}