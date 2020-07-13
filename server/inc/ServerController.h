#ifndef SERVERCONTR_H
#define SERVERCONTR_H

#include "TCPConnection.h"
#include "ServerConf.h"
#include "Logger.h"
#include "DB.h"
#include "JsonParser.h"

#define ERRORMESSAGESIZE 128

void RegisterClient(int socket, const char* message);
void LogIn(int socket, const char* message);
void GetClientData(int socket, const char* message);
void LogOut(int socket, const char* message);

#endif