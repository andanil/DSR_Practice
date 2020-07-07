#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdio.h>
#include<json.h>
#include <string.h>
#include "TCPConnection.h"

int JsonWriteGPSInfo(const char* filename, GPSInfo* data);
int JsonWriteGPSInfoWithId(const char* filename, Data* data);
const char* JsonSendGPSInfo(MessageType messageType, int id, GPSInfo* data);
const char* JsonSendUser(MessageType messageType, User* user);
const char* JsonSendErrorMessage(MessageType messageType, const char* mess);
const char* JsonSendSuccessMessage(MessageType messageType);
MessageType JsonGetMessageType(const char* data);
const char* JsonGetErrorMessage(const char* data);
User* JsonGetUser(const char* data);
Data* JsonGetData(const char* data);

#endif