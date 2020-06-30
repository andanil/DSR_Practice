#include "ClientDataController.h"

extern int run;
extern int sendToServer;

void *DataSendingHandler(void *ptr);

void RunDataSending(int socket)
{
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
			while(run)
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
			while(run)
			{
				char message[NMEAMESSAGESIZE];
				read(fd[0], message, NMEAMESSAGESIZE);
				GPSInfo* data = ParseRMCString(message);
    			WriteDataToJsonFile(data);
    			if(sendToServer)
    			{
				    if(SendUserData(socket, data))
				    	Log(LOGGERFILENAME, "SRVCON_INFO", "Sent data successfully");
    			}
			}
		}
	}

	pthread_exit(0);
}