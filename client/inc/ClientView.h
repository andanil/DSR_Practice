#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H

#include <string.h>
#include "TCPConnection.h"
#include "ClientConf.h"
#include "Logger.h"
#include "TCPClient.h"
#include "ServerConnController.h"

void RunApp(const char* ip, int port);

#endif