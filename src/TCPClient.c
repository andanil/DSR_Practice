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
        return 0; 
    } 
   
    if (connect(socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    { 
        return 0; 
    }
    return 1;
}