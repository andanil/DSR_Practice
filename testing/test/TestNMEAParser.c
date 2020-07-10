#include "unity.h"
#include "NMEAParser.h"

#define NAN -9223372036854775808

char message[80];
void setUp (void) {}
void tearDown (void) {} 

void TestFullString(void)
{
	strcpy(message, "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W,A*6A");
	GPSInfo *data = ParseRMCString(message);

	TEST_ASSERT_EQUAL_STRING("123519", data->time);
	TEST_ASSERT_EQUAL_STRING("A", data->status);
	TEST_ASSERT_EQUAL(4807.038, data->latitude);
	TEST_ASSERT_EQUAL_STRING("N", data->northOrSouth);
	TEST_ASSERT_EQUAL(1131.000, data->longitude);
	TEST_ASSERT_EQUAL_STRING("E", data->westOrEast);
	TEST_ASSERT_EQUAL(22.4, data->speed);
	TEST_ASSERT_EQUAL(84.4, data->direction);
	TEST_ASSERT_EQUAL_STRING("230394", data->date);
	TEST_ASSERT_EQUAL(3.1, data->declination);
	TEST_ASSERT_EQUAL_STRING("W", data->decWestOrEast);
	TEST_ASSERT_EQUAL_STRING("A", data->modeInd);
}

void TestStringWithEmptyDouble(void)
{
	strcpy(message, "$GPRMC,123519,A,,N,03710.1401,E,0.0,,190507,9.3,E,A*1F");
	GPSInfo *data = ParseRMCString(message);

	TEST_ASSERT_EQUAL_STRING("123519", data->time);
	TEST_ASSERT_EQUAL_STRING("A", data->status);
	TEST_ASSERT_EQUAL(NAN, data->latitude);
	TEST_ASSERT_EQUAL_STRING("N", data->northOrSouth);
	TEST_ASSERT_EQUAL(3710.1401, data->longitude);
	TEST_ASSERT_EQUAL_STRING("E", data->westOrEast);
	TEST_ASSERT_EQUAL(0, data->speed);
	TEST_ASSERT_EQUAL(NAN, data->direction);
	TEST_ASSERT_EQUAL_STRING("190507", data->date);
	TEST_ASSERT_EQUAL(9.3, data->declination);
	TEST_ASSERT_EQUAL_STRING("E", data->decWestOrEast);
	TEST_ASSERT_EQUAL_STRING("A", data->modeInd);
}

void TestStringWithEmptyChars(void)
{
	strcpy(message, "$GPRMC,,A,4807.038,,03710.1401,E,0.0,0,190507,9.3,,*1F");
	GPSInfo *data = ParseRMCString(message);

	TEST_ASSERT_EQUAL_STRING("", data->time);
	TEST_ASSERT_EQUAL_STRING("A", data->status);
	TEST_ASSERT_EQUAL(4807.038, data->latitude);
	TEST_ASSERT_EQUAL_STRING("", data->northOrSouth);
	TEST_ASSERT_EQUAL(3710.1401, data->longitude);
	TEST_ASSERT_EQUAL_STRING("E", data->westOrEast);
	TEST_ASSERT_EQUAL(0, data->speed);
	TEST_ASSERT_EQUAL(0, data->direction);
	TEST_ASSERT_EQUAL_STRING("190507", data->date);
	TEST_ASSERT_EQUAL(9.3, data->declination);
	TEST_ASSERT_EQUAL_STRING("", data->decWestOrEast);
	TEST_ASSERT_EQUAL_STRING("", data->modeInd);
}

void TestAnotherTypeOfString(void)
{
	strcpy(message, "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47");
	GPSInfo *data = ParseRMCString(message);

	TEST_ASSERT_NULL(data);
}

void TestEmptyString(void)
{
	strcpy(message, "");
	GPSInfo *data = ParseRMCString(message);

	TEST_ASSERT_NULL(data);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(TestFullString);
	RUN_TEST(TestStringWithEmptyDouble);
	RUN_TEST(TestStringWithEmptyChars);
	RUN_TEST(TestAnotherTypeOfString);
	RUN_TEST(TestEmptyString);
	return UNITY_END();
}