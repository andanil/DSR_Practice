#ifndef CLIENTDATACONT_H
#define CLIENTDATACONT_H

#include <unistd.h>
#include <pthread.h> 
#include "ClientView.h"
#include "ServerConnController.h"
#include "NMEAGenerator.h"
#include "NMEAParser.h"
#include "JsonParser.h"

void RunDataSending(int socket);

#endif