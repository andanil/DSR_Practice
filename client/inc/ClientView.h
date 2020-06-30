#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H

#include <string.h>
#include "TCPConnection.h"
#include "ClientConf.h"
#include "TCPClient.h"
#include "Logger.h"
#include "ServerConnController.h"
#include "ClientDataController.h"

void RunApp(const char* ip, int port);

#endif