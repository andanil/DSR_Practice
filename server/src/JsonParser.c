#include "JsonParser.h"

void WriteDataToJsonFile(Data* data)
{
	json_object* jobj = json_object_new_object();

	json_object* jid = json_object_new_int(data->userId);
	json_object* jtime = json_object_new_string(data->data.time);
	json_object* jstatus = json_object_new_string(data->data.status);
	json_object* jlatitude = json_object_new_double(data->data.latitude);
	json_object* jnorthOrSouth = json_object_new_string(data->data.northOrSouth);
	json_object* jlongitude = json_object_new_double(data->data.longitude);
	json_object* jwestOrEast = json_object_new_string(data->data.westOrEast);
	json_object* jspeed = json_object_new_double(data->data.speed);
	json_object* jdirection = json_object_new_double(data->data.direction);
	json_object* jdate = json_object_new_string(data->data.date);
	json_object* jdeclination = json_object_new_double(data->data.declination);
	json_object* jdecWestOrEast = json_object_new_string(data->data.decWestOrEast);
	json_object* jmodeInd = json_object_new_string(data->data.modeInd);

	json_object_object_add(jobj,"UserId", jid);
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

	FILE *file = fopen(JSONFILENAME, "a");
	if(file == NULL)
		Log(LOGGERFILENAME, "JSON_ERROR", "Write data to json failed");
	fprintf(file, "%s\n", json_object_to_json_string(jobj));
	fclose(file);
	Log(LOGGERFILENAME, "JSON_INFO", "Write data to json successfully");
}