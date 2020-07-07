#include "JsonParser.h"

User parsedUser;
Data parsedData;

void AddGPSInfoToObj(json_object* jobj, GPSInfo* data);

int JsonWriteGPSInfo(const char* filename, GPSInfo* data)
{
	FILE *file = fopen(filename, "a");
	if(file == NULL)
		return 0;

	json_object* jobj = json_object_new_object();
	AddGPSInfoToObj(jobj, data);

	fprintf(file, "%s\n", json_object_to_json_string(jobj));
	fclose(file);
	return 1;
}

int JsonWriteGPSInfoWithId(const char* filename, Data* data)
{
	FILE *file = fopen(filename, "a");
	if(file == NULL)
		return 0;

	json_object* jobj = json_object_new_object();
	json_object* jid = json_object_new_int(data->userId);
	json_object_object_add(jobj,"UserId", jid);
	AddGPSInfoToObj(jobj, &data->data);

	fprintf(file, "%s\n", json_object_to_json_string(jobj));
	fclose(file);
	return 1;
}

const char* JsonSendGPSInfo(MessageType messageType, int id, GPSInfo* data)
{
	json_object* jobj = json_object_new_object();
	json_object* jmessType = json_object_new_int(messageType);
	json_object* jid = json_object_new_int(id);
	json_object_object_add(jobj,"MessageType", jmessType);
	json_object_object_add(jobj,"UserId", jid);
	AddGPSInfoToObj(jobj, data);

	return json_object_to_json_string(jobj);
}

const char* JsonSendUser(MessageType messageType, User* user)
{
	json_object* jobj = json_object_new_object();
	json_object* jmessType = json_object_new_int(messageType);
	json_object* jid = json_object_new_int(user->id);
	json_object* jlogin = json_object_new_string(user->login);
	json_object* jpass = json_object_new_string(user->password);

	json_object_object_add(jobj,"MessageType", jmessType);
	json_object_object_add(jobj,"UserId", jid);
	json_object_object_add(jobj,"Login", jlogin);
	json_object_object_add(jobj,"Password", jpass);

	return json_object_to_json_string(jobj);
}

const char* JsonSendErrorMessage(MessageType messageType, const char* mess)
{
	json_object* jobj = json_object_new_object();
	json_object* jmessType = json_object_new_int(messageType);
	json_object* jerror = json_object_new_string(mess);

	json_object_object_add(jobj,"MessageType", jmessType);
	json_object_object_add(jobj,"Error", jerror);

	return json_object_to_json_string(jobj);
}

const char* JsonSendSuccessMessage(MessageType messageType)
{
	json_object* jobj = json_object_new_object();
	json_object* jmessType = json_object_new_int(messageType);

	json_object_object_add(jobj,"MessageType", jmessType);

	return json_object_to_json_string(jobj);
}

MessageType JsonGetMessageType(const char* data)
{
	json_object* jobj = json_tokener_parse(data);
	MessageType mess = (MessageType)json_object_get_int(json_object_object_get(jobj,"MessageType"));
	return mess;
}

const char* JsonGetErrorMessage(const char* data)
{
	json_object* jobj = json_tokener_parse(data);
	const char* mess = json_object_get_string(json_object_object_get(jobj,"Error"));
	return mess;
}

User* JsonGetUser(const char* data)
{
	json_object* jobj = NULL;
	jobj = json_tokener_parse(data);
	if(jobj == NULL)
		return NULL;

	parsedUser.id = json_object_get_int(json_object_object_get(jobj,"UserId"));
	strcpy(parsedUser.login, json_object_get_string(json_object_object_get(jobj,"Login")));
	strcpy(parsedUser.password, json_object_get_string(json_object_object_get(jobj,"Password")));
	return &parsedUser;
}

Data* JsonGetData(const char* data)
{
	json_object* jobj = NULL;
	jobj = json_tokener_parse(data);
	if(jobj == NULL)
		return NULL;

	parsedData.userId = json_object_get_int(json_object_object_get(jobj,"UserId"));
	strcpy(parsedData.data.time, json_object_get_string(json_object_object_get(jobj,"Time")));
	strcpy(parsedData.data.status, json_object_get_string(json_object_object_get(jobj,"Status")));
	parsedData.data.latitude = json_object_get_double(json_object_object_get(jobj,"Latitude"));
	strcpy(parsedData.data.northOrSouth, json_object_get_string(json_object_object_get(jobj,"NorthOrSouth")));
	parsedData.data.longitude = json_object_get_double(json_object_object_get(jobj,"Longitude"));
	strcpy(parsedData.data.westOrEast, json_object_get_string(json_object_object_get(jobj,"WestOrEast")));
	parsedData.data.speed = json_object_get_double(json_object_object_get(jobj,"Speed"));
	parsedData.data.direction = json_object_get_double(json_object_object_get(jobj,"Direction"));
	strcpy(parsedData.data.date, json_object_get_string(json_object_object_get(jobj,"Date")));
	parsedData.data.declination = json_object_get_double(json_object_object_get(jobj,"Declination"));
	strcpy(parsedData.data.decWestOrEast, json_object_get_string(json_object_object_get(jobj,"DecWestOrEast")));
	strcpy(parsedData.data.modeInd, json_object_get_string(json_object_object_get(jobj,"ModeInd")));

	return &parsedData;
}

void AddGPSInfoToObj(json_object* jobj, GPSInfo* data)
{
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
}