#include <syslog.h>
#include "TCPConnection.h"

int Send(int socket, message_t* message)
{
	if(socket < 0) 
	{
		return 0;
	}
	openlog("connection",LOG_PID,LOG_USER); 
	if(send(socket, message, sizeof(*message), 0) < 0)
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
	message_t* message = (message_t *)malloc(sizeof(message_t));
	if( recv(socket, message, sizeof(message_t), 0) < 0)
  	{
  		syslog(LOG_ERR,"Receive failed");
  		closelog();
		return NULL;
  	}
  	syslog(LOG_INFO,"Message has been received");
  	closelog();
  	return message;
}