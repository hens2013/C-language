#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "Airport.h"
#include "General.h"


int		isSameAirport(const Airport* pPort1, const Airport* pPort2)
{
	if (!pPort1 || !pPort2)
		return 0;
	if (strcmp(pPort1->code, pPort2->code) == 0)
		return 1;

	return 0;
}

int		isAirportCode(const Airport* pPort1, const char* code)
{
	if (!pPort1)
		return 0;
	if (strcmp(pPort1->code, code) == 0)
		return 1;

	return 0;


}

//Haversine
//	formula : a = sin²(Δφ / 2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ / 2)
//	c = 2 ⋅ atan2(√a, √(1−a))
//	d = R ⋅ c
//where	φ is latitude, λ is longitude, R is earth’s radius(mean radius = 6, 371km);
//note that angles need to be in radians to pass to trig functions!
double	distance(const Airport* pPort1, const Airport* pPort2)
{
	double lat1_rad = toRad(pPort1->latitude);
	double long1_rad = toRad(pPort1->longitude);
	double lat2_rad = toRad(pPort2->latitude);
	double long2_rad = toRad(pPort1->longitude);

	double s_lat = sin(lat1_rad - lat2_rad);
	double s_log = sin(long1_rad - long2_rad);
	double a = s_lat*s_lat + cos(lat1_rad)*cos(lat2_rad)*s_log*s_log;
	double r_a = sqrt(a);
	double r_a_1 = sqrt(1 - a);
	double c = 2* atan2(r_a, r_a_1);
	double d = EART_R*c*KM_MILE;
	return d;
}



void	printAirport(const Airport* pPort)
{
	printf("Airport name:%s\t", pPort->name);
	printf("Country: %s\t Code:%s\n", pPort->country,pPort->code);
	printf("Latitude: %.2lf\t Longitude: %.2lf\n", pPort->latitude,pPort->longitude);
}

void	initAirportNoCode(Airport* pPort)
{
	getAirportName(pPort);
	pPort->country = getStrExactName("Enter airport country");
	pPort->latitude = getDoubleCheckLimits("Enter airport latitude in degree", -90, 90);
	pPort->longitude = getDoubleCheckLimits("Enter airport longitude in degree", -180, 180);
}

void	getAirportName(Airport* pPort)
{
	char temp[255];
	char nameBuilder[255];
	char* delimiters = " ";
	char* word;
	
	printf("Enter airport name");
	myGets(temp, MAX_STR_LEN,stdin);
	nameBuilder[0] = '\0';
	int first = 1;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		*word = toupper(*word);
		if (!first)
			strcat(nameBuilder, " ");
		strcat(nameBuilder, word);
		first = 0;
		word = strtok(NULL, delimiters);
	}

	pPort->name = (char*)malloc((strlen(nameBuilder) + 1) * sizeof(char));
	if (!pPort->name)
		return;

	strcpy(pPort->name, nameBuilder);
}

void	initAirportCode(Airport* pPort)
{
	getCode(pPort->code);
}

void getCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d letters\t",CODE_LENGTH);
		myGets(temp, MAX_STR_LEN,stdin);
		if (strlen(temp) != CODE_LENGTH)
		{
			printf("code should be %d letters\n",CODE_LENGTH);
			ok = 0;
		}
		else {
			for (int i = 0; i < 3; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

int checkUniqeCode(const char* code, Airport* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(code, arr[i].code) == 0)
			return 0;
	}
	return 1;
}



void	freeAirport(Airport* pPort)
{
	free(pPort->name);
	free(pPort->country);
}

double	toRad(double degree)
{
	return (degree*M_PI) / 180;
}
void readAirportDataFromFile(Airport* airport, FILE* file) {

	airport->name = getStrExactLength(file);
	if (strlen(airport->name) == 0)
	{
		airport->name = getStrExactLength(file);
	}
	airport->country = getStrExactLength(file);
	fscanf(file, "%s", airport->code);
	fscanf(file, "%lf %lf", &(airport->latitude), &(airport->longitude));


}
void saveAirportDataFromFile(Airport* airport, FILE* file) {

	/*fputs(airport->name, file);
	fputs(airport->country, file);
	fprintf(file, "%s\n",airport->code);
	fprintf(file, "%lf %lf\n", airport->longitude, airport->latitude);*/
	printf( "%s\n%s\n%s\n%f %f\n",
		airport->name, airport->country, airport->code, airport->latitude, airport->longitude);
	fprintf(file, "%s\n%s\n%s\n%f %f\n",
		airport->name, airport->country, airport->code, airport->latitude, airport->longitude);

}