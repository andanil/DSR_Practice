#ifndef SERVERCONTR_H
#define SERVERCONTR_H

#include "TCPConnection.h"
#include "ServerConf.h"
#include "Logger.h"
#include "DB.h"

void RegisterClient(int socket, User* user);
void LogIn(int socket, User* user);
void GetClientData(int socket, User* user);

#endif