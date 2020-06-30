#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdio.h>
#include <json.h>
#include "TCPConnection.h"
#include "ServerConf.h"
#include "Logger.h"

void WriteDataToJsonFile(Data* data);

#endif