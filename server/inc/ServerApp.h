#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <stdio.h> 
#include <stdlib.h> 
#include "TCPConnection.h"
#include "ServerConf.h"
#include "Logger.h"

void RunThreadApp(const char* ip, int socket);

#endif