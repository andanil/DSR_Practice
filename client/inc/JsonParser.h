#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdio.h>
#include<json.h>
#include "GPSInfo.h"
#include "ClientConf.h"
#include "Logger.h"

const char* GenerateJsonString(GPSInfo* data);
void WriteDataToJsonFile(GPSInfo* data);

#endif