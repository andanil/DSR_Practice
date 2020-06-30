#include <stdio.h> 
#include <stdlib.h>
#include "ClientView.h"
   
int main(int argc, char const *argv[]) 
{ 
    if(argc < 2) 
    {
        printf("Arguments have been expected\n"); 
        return 0;
    }

    RunApp(argv[1], 8080);
    return 0; 
} 