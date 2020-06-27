#include "Logger.h"

void CurrentTime();
static char buff[128];

void Log(const char* filename, const char* status, const char* message)
{
	FILE *file = fopen(filename, "a");
	CurrentTime();
	fprintf(file, "%s %s %s\n", buff, status, message);
	fclose(file);
}

void CurrentTime()
{
	time_t now = time(NULL);
	strftime(buff, 128, "%Y-%m-%d %H:%M:%S", localtime(&now));
}