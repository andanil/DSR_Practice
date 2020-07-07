#ifndef USER_H
#define USER_H

#define DATASIZE 128

typedef struct
{
	int id;
	char login[DATASIZE];
	char password [DATASIZE];
}User;

#endif