#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H

#include <string.h>
#include "TCPConnection.h"
#include "ClientConf.h"
#include "TCPClient.h"
#include "Logger.h"
#include "ServerConnController.h"
#include "ClientDataController.h"

typedef int run_app_t;

enum run_app_e
{
	OFF = 0,
	ON,
};

typedef int auth_menu_t;

enum auth_menu_e
{
	SETTINGS = 1,
	LOG_OUT,
	EXIT,
};

typedef int unauth_menu_t;

enum unauth_menu_e
{
	REGISTER_USER = 1,
	LOG_IN,
	AUTO_LOG_IN,
	EXIT_PROG,
};

typedef int settings_menu_t;

enum settings_menu_e
{
  CHANGE = 1,
  EXIT_MENU,
};


void RunApp(const char* ip, int port);

#endif