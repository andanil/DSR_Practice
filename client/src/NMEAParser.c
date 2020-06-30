#include "NMEAParser.h"

GPSInfo data;
char item[32];

void ParseChars(char* string, char* inf);
void ParseChar(char* string, char* inf);
void ParseDouble(char* string, double* inf);
int GetNextItem(char* array);
void DeleteChars(char* array, int count);

GPSInfo* ParseRMCString(char* string)
{
	if(!GetNextItem(string))
		return NULL;
	if(strcmp(item, "$GPRMC") != 0)
	{
		Log(LOGGERFILENAME, "RMCPARSER_INFO", "Not RMC string");
		return NULL;
	}
	ParseChars(string, data.time);
	ParseChar(string, data.status);
	ParseDouble(string, &data.latitude);
	ParseChar(string, data.northOrSouth);
	ParseDouble(string, &data.longitude);
	ParseChar(string, data.westOrEast);
	ParseDouble(string, &data.speed);
	ParseDouble(string, &data.direction);
	ParseChars(string, data.date);
	ParseDouble(string, &data.declination);
	ParseChar(string, data.decWestOrEast);
	ParseChar(string, data.modeInd);

	return &data;
}

void ParseChars(char* string, char* inf)
{
	if(!GetNextItem(string))
		strcpy(inf, "NULL");
	strcpy(inf, item);
}

void ParseChar(char* string, char* inf)
{
	if(!GetNextItem(string))
		strcpy(inf, "\n");
	strcpy(inf, item);
}

void ParseDouble(char* string, double* inf)
{
	if(!GetNextItem(string))
		*inf = NAN;
	*inf = atof(item);
}

int GetNextItem(char* array)
{
	int count = 0;
	memset(item, 0, sizeof(item));
	while(array[count] != ',' && array[count] != '*' && count<strlen(array))
		count++;
	if(!count)
	{
		DeleteChars(array, 1);
		return 0;
	}
	strncpy(item, array, count);
	DeleteChars(array, count+1);
	return 1;
}

void DeleteChars(char* array, int count)
{
	char first = array[0];
	for(int i = 0; i < strlen(array) - count; i++)
		array[i] = array[i+count];
	array[strlen(array)-count+1] = '\0';
}