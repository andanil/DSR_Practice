#ifndef SERVERCONCONTR_H
#define SERVERCONCONTR_H

#include <string.h>
#include "ClientView.h"
#include "TCPConnection.h"
#include "ClientConf.h"
#include "Logger.h"
#include "FileAuthorization.h"
#include "Logger.h"
#include "JsonParser.h"

const char* Register(int socket, const char* login, const char* password, const char* confPassword);
const char* LogIn(int socket, const char* login, const char* password);
const char* AutoLogIn(int socket);
const char* LogOut(int socket);
int SendUserData(int socket, GPSInfo* data);

#endif