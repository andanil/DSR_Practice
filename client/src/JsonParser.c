#include "JsonParser.h"

const char* GenerateJsonString(GPSInfo* data)
{
	json_object* jobj = json_object_new_object();

	json_object* jtime = json_object_new_string(data->time);
	json_object* jstatus = json_object_new_string(data->status);
	json_object* jlatitude = json_object_new_double(data->latitude);
	json_object* jnorthOrSouth = json_object_new_string(data->northOrSouth);
	json_object* jlongitude = json_object_new_double(data->longitude);
	json_object* jwestOrEast = json_object_new_string(data->westOrEast);
	json_object* jspeed = json_object_new_double(data->speed);
	json_object* jdirection = json_object_new_double(data->direction);
	json_object* jdate = json_object_new_string(data->date);
	json_object* jdeclination = json_object_new_double(data->declination);
	json_object* jdecWestOrEast = json_object_new_string(data->decWestOrEast);
	json_object* jmodeInd = json_object_new_string(data->modeInd);

	json_object_object_add(jobj,"Time", jtime);
	json_object_object_add(jobj,"Status", jstatus);
	json_object_object_add(jobj,"Latitude", jlatitude);
	json_object_object_add(jobj,"NorthOrSouth", jnorthOrSouth);
	json_object_object_add(jobj,"Longitude", jlongitude);
	json_object_object_add(jobj,"WestOrEast", jwestOrEast);
	json_object_object_add(jobj,"Speed", jspeed);
	json_object_object_add(jobj,"Direction", jdirection);
	json_object_object_add(jobj,"Date", jdate);
	json_object_object_add(jobj,"Declination", jdeclination);
	json_object_object_add(jobj,"DecWestOrEast", jdecWestOrEast);
	json_object_object_add(jobj,"ModeInd", jmodeInd);

	return json_object_to_json_string(jobj);
}

void WriteDataToJsonFile(GPSInfo* data)
{
	FILE *file = fopen(JSONFILENAME, "a");
	if(file == NULL)
		Log(LOGGERFILENAME, "JSON_ERROR", "Write data to json failed");
	fprintf(file, "%s\n", GenerateJsonString(data));
	fclose(file);
	Log(LOGGERFILENAME, "JSON_INFO", "Write data to json successfully");
}