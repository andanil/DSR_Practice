#ifndef GPSINFO_H
#define GPSINFO_H

#include <math.h>

typedef struct
{
	char time[11];
	char status[1];
	double latitude;
	char northOrSouth[1];
	double longitude;
	char westOrEast[1];
	double speed;
	double direction;
	char date[6];
	double declination;
	char decWestOrEast[1];
	char modeInd[1];
}GPSInfo;

#endif