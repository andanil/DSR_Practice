#ifndef FILEAUTH_H
#define FILEAUTH_H

#include "ClientConf.h"
#include "User.h"
#include "Logger.h"

int WriteData(User* user);
int ReadData(User* user);

#endif