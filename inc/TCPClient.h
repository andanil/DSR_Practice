#ifndef TCPCCLIENT_H
#define TCPCCLIENT_H

#include "TCPConnection.h"

int InitTCPClient();
int Connect(int socket, int port, const char* address);


#endif