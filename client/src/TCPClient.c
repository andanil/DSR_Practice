#include "TCPClient.h"

int InitTCPClient()
{
	return socket(AF_INET, SOCK_STREAM, 0);
}

int Connect(int socket, int port, const char* address)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; 
    addr.sin_port = htons(port); 
       
    if(inet_pton(AF_INET, address, &addr.sin_addr)<=0)  
    { 
        Log(LOGGERFILENAME, "TCP_ERROR", "Incorrect address");
        return RET_ERROR; 
    } 
   
    if (connect(socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        Log(LOGGERFILENAME, "TCP_ERROR", "Connect failed"); 
        return RET_ERROR; 
    }
    return RET_OK;
}