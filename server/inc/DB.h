#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "User.h"
#include "UserList.h"
#include "Logger.h"
#include "ServerConf.h"

#define SERVER "localhost"
#define USER "gps_user"
#define PASSWORD "userpswd"
#define DATABASE "gps_db"
#define MAXBUFFERSIZE 300

static MYSQL* connection;

int ConnectToDB();
int InsertUserValue(User* user);
UserListNode* GetAllUsers();
User* GetUserByName(const char* username);
void CloseDB();

#endif