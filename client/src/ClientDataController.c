#include "ClientDataController.h"

extern int generateCoord;
extern int sendToServer;

void *DataSendingHandler(void *ptr);
void ResendUserData(int socket, GPSInfo* data);

void RunDataSending(int socket)
{
	generateCoord = ON;
	pthread_t thread;
	int *arg = malloc(sizeof(*arg));
	*arg = socket;
	pthread_create(&thread, 0, DataSendingHandler, arg);
	pthread_detach(thread);
}

void *DataSendingHandler(void *ptr)
{
	int fd[2];
	pipe(fd);
	int pid = fork();
	switch(pid)
	{
		case -1:
		{
			Log(LOGGERFILENAME, "APP_ERROR", "Cannot create fork");
			break;
		}
		case 0:
		{
			close(fd[0]);
			while(generateCoord)
			{
				sleep(PERIOD);
				write(fd[1], GetRMCString(), NMEAMESSAGESIZE);
			}
			break;
		}
		default:
		{
			close(fd[1]);
			int socket = *((int*) ptr);
			free(ptr);
			while(generateCoord)
			{
				char message[NMEAMESSAGESIZE];
				read(fd[0], message, NMEAMESSAGESIZE);
				GPSInfo* data = ParseRMCString(message);
    			if(JsonWriteGPSInfo(JSONFILENAME, data) == RET_ERROR)
    				Log(LOGGERFILENAME, "JSON_ERROR", "Write data to json failed");
    			else
    				Log(LOGGERFILENAME, "JSON_INFO", "Write data to json successfully");
    			
    			if(sendToServer)
    			{
				    if(SendUserData(socket, data) == RET_OK)
				    	Log(LOGGERFILENAME, "SRVCON_INFO", "Sent data successfully");
				    else
				    	ResendUserData(socket, data);
    			}
			}
		}
	}

	pthread_exit(0);
}

void ResendUserData(int socket, GPSInfo* data)
{
	int count = 0;
	int send = RET_ERROR;
	while(count < REPEATNUM && send == RET_ERROR)
	{	
		send = SendUserData(socket, data);
		if(send == RET_OK)
	    	Log(LOGGERFILENAME, "SRVCON_INFO", "Sent data successfully");
	    count++;
	}
}