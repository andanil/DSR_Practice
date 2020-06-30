#ifndef NMEAPARSER_H
#define NMEAPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GPSInfo.h"
#include "ClientConf.h"
#include "Logger.h"

GPSInfo* ParseRMCString(char* string);

#endif