#ifndef GPSINFO_H
#define GPSINFO_H

#include <math.h>

typedef struct
{
	char time[11];
	char status[2];
	double latitude;
	char northOrSouth[2];
	double longitude;
	char westOrEast[2];
	double speed;
	double direction;
	char date[6];
	double declination;
	char decWestOrEast[2];
	char modeInd[2];
}GPSInfo;

#endif