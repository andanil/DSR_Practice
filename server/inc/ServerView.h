#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <pthread.h> 
#include "ServerController.h"
#include "UserList.h"

typedef int menu_t;

enum menu_e
{
	VIEW_USERS = 1,
	DELETE_USER,
};

void *MainMenu();

#endif