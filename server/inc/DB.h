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
#include "conf.h"
#include "TCPConnection.h"

#define SERVER "localhost"
#define USER "gps_user"
#define PASSWORD "userpswd"
#define DATABASE "gps_db"
#define MAXBUFFERSIZE 300

static MYSQL* connection;
static int isConnected = 0;

int ConnectToDB();
int InsertUserValue(User* user);
int DeleteUserById(int id);
int InsertGPSData(Data* data);
UserListNode* GetAllUsers();
User* GetUserByName(const char* username);
void CloseDB();

#endif