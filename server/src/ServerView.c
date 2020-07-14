#include "ServerView.h"

void ViewMainMenu();
void ViewUsers();
void DeleteUserView();

void *MainMenu()
{
	while(1)
        ViewMainMenu();
}

void ViewMainMenu()
{
    printf("\nChoose command:\n"); 
    printf("1.View all users\n"); 
    printf("2.Delete user\n"); 

    int command;
    if(scanf("%d", &command)) 
    {
        switch(command)
        {
            case VIEW_USERS:
            {
                ViewUsers();   
                break;
            }
            case DELETE_USER:
            {
                DeleteUserView();
                break;
            }
            default:
                printf("Unknown command\n");
        }
    }
}

void ViewUsers()
{
	UserListNode* head = GetUsers();
	if(head == NULL)
	{
		printf("Cannot get users\n");   
		return;
	}

	UserListNode* user = head;
	while(user != NULL)
	{
		printf("%d %s %s\n", user->data->id, user->data->login, user->data->password);
		user = user->next;
	}
	FreeList(head);
}

void DeleteUserView()
{
	printf("Print user's id\n"); 

    int id;
    if(!scanf("%d", &id)) 
    {
		printf("Incorrect input\n");   
		return;
    }

    if(DeleteUser(id) == RET_ERROR)
    {
    	Log(LOGGERFILENAME, "SRVCON_ERROR", "Deleting user failed");
        printf("%s\n", "Deleting user failed");
        return;
    }
    Log(LOGGERFILENAME, "SRVCON_ERROR", "Deleting user completed successfully");
    printf("%s\n", "Deleting user completed successfully");
}