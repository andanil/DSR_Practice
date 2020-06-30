#include "NMEAGenerator.h"

char date[16];
char currTime[32];
char message[NMEAMESSAGESIZE];

void CurrentDate();
void CurrentTimeOnly();
double RandomDouble(double start, double end);
int CalculateChecksum(char *data);

char* GetRMCString()
{
	static double latitude = 1255.15;
	static double longitude = 3500.35;
	
	strcpy(message, "$GPRMC,");
	CurrentTimeOnly();
	strcat(message, currTime);
	strcat(message, ",A,");

	char arr[sizeof(double)];
	sprintf(arr, "%4.2f", latitude);
	latitude ++;
	strcat(message, arr);
	strcat(message, ",N,");

	sprintf(arr, "%5.2f", longitude);
	longitude++;
	strcat(message, arr);
	strcat(message, ",E,");

	double speed = RandomDouble(0, 10);
	sprintf(arr, "%2.2f", speed);
	strcat(message, arr);

	strcat(message, ",");

	double direction = RandomDouble(0, 50);
	sprintf(arr, "%2.2f", direction);
	strcat(message, arr);
	strcat(message, ",");

	CurrentDate();
	strcat(message, date);
	strcat(message, ",");

	double declination = RandomDouble(0, 5);
	sprintf(arr, "%1.2f", declination);
	strcat(message, arr);
	strcat(message, ",W,*");

	sprintf(arr, "%x", CalculateChecksum(message));
	strcat(message, arr);
	return message;
}

void CurrentDate()
{
	time_t now = time(NULL);
	strftime(date, 16, "%d%m%y", localtime(&now));
}

void CurrentTimeOnly()
{
	time_t now = time(NULL);
	strftime(currTime, 32, "%H%M%S", localtime(&now));
}

double RandomDouble(double start, double end)
{
    srand(time(NULL));
    return (double)rand()/RAND_MAX*(end-start) - start;
}

int CalculateChecksum(char *data)
{
    int checksum = 0;
    int i;
    for (i = 1; i < strlen(data) - 1; i ++) {
        checksum ^= data[i];
    }

    return checksum;
}