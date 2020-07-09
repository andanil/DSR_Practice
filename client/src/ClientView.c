#include "ClientView.h"

int run;
int sendToServer;
User user;

void MainMenu(int socket);
void AuthMenu(int socket);
void UnauthMenu(int socket);
void RegisterView(int socket);
void LogInView(int socket);
void SetAutoLogIn();
void SettingsMenu();
int LogInResView(const char* res, int socket);
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
    if(Connect(socket, port, ip) == RET_ERROR)
    {
        Log(LOGGERFILENAME, "TCP_ERROR", "Socket connection error");
        return;
    }
    Log(LOGGERFILENAME, "TCP_INFO", "Connect to server successfully");

    user.id = -1;
    sendToServer = 0;
    run = 1;
    
    while(run)
        MainMenu(socket);

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
	printf("\nYou have logged in as %s\n", user.login); 
	printf("Choose command:\n"); 
    printf("1.Settings\n"); 
    printf("2.Exit\n"); 

    int command;
    if(scanf("%d", &command)) 
    {
        switch(command)
        {
            case SETTINGS:
            {
             	SettingsMenu();   
                break;
            }
            case EXIT:
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
    printf("3.Auto log in\n"); 
    printf("4.Exit\n"); 

    int command;
    if(scanf("%d", &command)) 
    {
        switch(command)
        {
            case REGISTER_USER:
            {
             	RegisterView(socket);   
                break;
            }
            case LOG_IN:
            {
                LogInView(socket);
                break;
            }
            case AUTO_LOG_IN:
            {
                LogInResView(AutoLogIn(socket), socket);
                break;
            }
            case EXIT_PROG:
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
	if(GetInput("Username:", name) == RET_ERROR)
		return;

    char password[DATASIZE];
    if(GetInput("Password:", password) == RET_ERROR)
		return;

	char confPassword[DATASIZE];
    if(GetInput("Confirm password:", confPassword) == RET_ERROR)
		return;

    const char* res = Register(socket, name, password, confPassword);
    if(strcmp(res, "Success") != 0)
    {
        Log(LOGGERFILENAME, "SRVCON_ERROR", "Registration failed");
        printf("%s\n", res);
        return;
    }
    Log(LOGGERFILENAME, "SRVCON_INFO", "Registration completed successfully");
    SetAutoLogIn();
    RunDataSending(socket);
}

void LogInView(int socket)
{
	char name[DATASIZE];
	if(GetInput("Username:", name) == RET_ERROR)
		return;

    char password[DATASIZE];
    if(GetInput("Password:", password) == RET_ERROR)
		return;

	if(LogInResView(LogIn(socket, name, password), socket) == RET_OK)
        SetAutoLogIn();
}

void SetAutoLogIn()
{
    printf("Make %s an auto login user? (y/n)\n", user.login);
    char answer;
    if(scanf("%s", &answer)) 
    {
        switch(answer)
        {
            case 'y':
            {
                if(!WriteData(&user))
                    printf("Write user info error\n");   
                break;
            }
            case 'n':
            {
                break;
            }
            default:
                printf("Unknown symbol\n");
        }
    }

}

void SettingsMenu()
{
    printf("\nSend data to server %s\n", sendToServer?"True":"False"); 
    printf("Choose command\n"); 
    printf("1.Change parameter\n"); 
    printf("2.Exit\n"); 

    int command;
    if(scanf("%d", &command)) 
    {
        switch(command)
        {
            case CHANGE:
            {
                sendToServer = !sendToServer;
                char* mess = (char*)malloc(DATASIZE*sizeof(char));
                strcpy(mess, "Set value ");
                strcat(mess, sendToServer?"True":"False");
                strcat(mess, " to sendToServer parameter");
                Log(LOGGERFILENAME, "APP_INFO", mess);
                free(mess);   
                break;
            }
            case EXIT_MENU:
            {
                break;
            }
            default:
                printf("Unknown command\n");
        }
    }
}

int LogInResView(const char* res, int socket)
{
    if(strcmp(res, "Success") != 0)
    {
        Log(LOGGERFILENAME, "SRVCON_ERROR", "Authorization failed");
        printf("%s\n", res);
        return RET_ERROR;
    }
    Log(LOGGERFILENAME, "SRVCON_INFO", "Authorization completed successfully");
    RunDataSending(socket);
    return RET_OK;
}

int GetInput(const char* message, char* data)
{
    ret_t ret = RET_OK;
    char temp;
    scanf("%c",&temp); 
	printf("%s\n", message);
    if(!scanf("%[^\n]", data))
    {
        printf("Incorrect input\n");   
        ret = RET_ERROR;
    }
    return ret;
}