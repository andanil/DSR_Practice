#include <syslog.h>
#include "TCPConnection.h"

static message_t message;

int Send(int socket, message_t* mess)
{
	if(socket < 0) 
	{
		return 0;
	}
	openlog("connection",LOG_PID,LOG_USER); 
	if(send(socket, mess, sizeof(*mess), 0) < 0)
	{
		syslog(LOG_ERR,"Send failed");
  		closelog();
		return 0;
	}
	syslog(LOG_INFO,"Message has been sent");
	closelog();
	return 1;
}

message_t* Read(int socket)
{
	openlog("connection",LOG_PID,LOG_USER); 
	if( recv(socket, &message, sizeof(message_t), 0) < 0)
  	{
  		syslog(LOG_ERR,"Receive failed");
  		closelog();
		return NULL;
  	}
  	syslog(LOG_INFO,"Message has been received");
  	closelog();
  	return &message;
}