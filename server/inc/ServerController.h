#ifndef SERVERCONTR_H
#define SERVERCONTR_H

#include "TCPConnection.h"
#include "ServerConf.h"
#include "Logger.h"
#include "DB.h"

void RegisterClient(int socket, User* newUser);
void LogIn(int socket, User* client);
void GetClientData(int socket, User* client);

#endif