#include "ClientView.h"

static int run;
User user;

void MainMenu(int socket);
void AuthMenu(int socket);
void UnauthMenu(int socket);
void RegisterView(int socket);
void LogInView(int socket);
void SendDataView(int socket);
int GetInput(const char* message, char* data);

void RunApp(const char* ip, int port)
{
	Log(LOGGERFILENAME, "TCP_INFO", "TCP client initialization");
    int socket = InitTCPClient(); 
    if(socket < 0)
    {
    	Log(LOGGERFILENAME, "TCP_ERROR", "Socket creation error");
    	return;
    }

	Log(LOGGERFILENAME, "TCP_INFO", "Connecting to server");
    if(!Connect(socket, port, ip))
    {
    	Log(LOGGERFILENAME, "TCP_ERROR", "Socket connection error");
        return;
    }

    user.id = -1;
   
    run = 1;
    while(run)
    {
    	MainMenu(socket);
    }

    Log(LOGGERFILENAME, "TCP_INFO", "TCP client closing");
    close(socket);
    return; 
}

void MainMenu(int socket)
{
	if(user.id == -1)
		UnauthMenu(socket);
	else
		AuthMenu(socket);
}

void AuthMenu(int socket)
{
	printf("\nYou have logged in as %s\n", user.name); 
	printf("Choose command:\n"); 
    printf("1.Send data\n"); 
    printf("2.Exit\n"); 

    int command;
    if(scanf("%d", &command)) 
    {
        switch(command)
        {
            case 1:
            {
             	SendDataView(socket);   
                break;
            }
            case 2:
            {
                run = 0;
                break;
            }
            default:
                printf("Unknown command\n");
        }
    }
}

void UnauthMenu(int socket)
{
	printf("\nChoose command:\n"); 
    printf("1.Register\n"); 
    printf("2.Log in\n"); 
    printf("3.Exit\n"); 

    int command;
    if(scanf("%d", &command)) 
    {
        switch(command)
        {
            case 1:
            {
             	RegisterView(socket);   
                break;
            }
            case 2:
            {
                LogInView(socket);
                break;
            }
            case 3:
            {
                run = 0;
                break;
            }
            default:
                printf("Unknown command\n");
        }
    }
}

void RegisterView(int socket)
{
    char name[DATASIZE];
	if(!GetInput("Username:", name))
		return;

    char password[DATASIZE];
    if(!GetInput("Password:", password))
		return;

	char confPassword[DATASIZE];
    if(!GetInput("Confirm password:", confPassword))
		return;

    const char* res = Register(socket, name, password, confPassword);
    if(strcmp(res, "Success") != 0)
    {
    	Log(LOGGERFILENAME, "SRVCON_ERROR", "Registration failed");
    	printf("%s\n", res);
    }
    Log(LOGGERFILENAME, "SRVCON_INFO", "Registration completed successfully");
}

void LogInView(int socket)
{
	char name[DATASIZE];
	if(!GetInput("Username:", name))
		return;

    char password[DATASIZE];
    if(!GetInput("Password:", password))
		return;

	const char* res = LogIn(socket, name, password);
    if(strcmp(res, "Success") != 0)
    {
    	Log(LOGGERFILENAME, "SRVCON_ERROR", "Authorization failed");
    	printf("%s\n", res);
    }
    Log(LOGGERFILENAME, "SRVCON_INFO", "Authorization completed successfully");
}

void SendDataView(int socket)
{
	const char* res = SendData(socket);
    if(strcmp(res, "Success") != 0)
    {
    	Log(LOGGERFILENAME, "SRVCON_ERROR", "Send data failed");
    	printf("%s\n", res);
    }
    printf("%s\n", "Sent data successfully");
    Log(LOGGERFILENAME, "SRVCON_INFO", "Sent data successfully");
}

int GetInput(const char* message, char* data)
{
    char temp;
    scanf("%c",&temp); 
	printf("%s\n", message);
    if(!scanf("%[^\n]", data))
    {
        printf("Incorrect input\n");   
        return 0;
    }
    return 1;
}