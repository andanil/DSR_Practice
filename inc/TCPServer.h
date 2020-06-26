#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "TCPConnection.h"
#include "ServerApp.h"

#define MAXCLIENT 10
#define NO_ERROR 0

typedef struct socket_descr_e
{
    int socket;
    const char* ip;
} socket_descr_t;

int StartTCPServer(int port);
int Accept(int server);

#endif