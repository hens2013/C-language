#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"
#include "Date.h"

int		isFlightInRoute(const Flight* pFlight,const char* codeSource, const char* codeDest)
{
	if ((isAirportCode(pFlight->pOriginAirport, codeSource) == 1) &&
		(isAirportCode(pFlight->pDestAirport, codeDest) == 1))
		return 1;

	return 0;
}

int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, 
		const char* codeDest)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isFlightInRoute(arr[i], codeSource, codeDest))
			count++;
	}
	return count;
}

double	flightTime(const Flight* pFlight)
{
	double dist = distance(pFlight->pDestAirport, pFlight->pOriginAirport);
	if(dist < 0)
		dist *= (-1);
	return dist / pFlight->milePerHour;
}



void	printFlight(const Flight* pFlight)
{
	printf("Flight From %s To %s\t",pFlight->pOriginAirport->code, pFlight->pDestAirport->code);
	printDate(pFlight->date);
	printf( "Hour: %d Speed: %.2lf\n", pFlight->hour, pFlight->milePerHour);
	double dist = distance(pFlight->pOriginAirport, pFlight->pDestAirport);
	printf("Flight distance  %.2lf miles\t", dist);
	double t = flightTime(pFlight);
	int h = (int)t;
	int m = (int)((t - h) * 60);
	printf("Flight length: hours %d  minutes: %d\n",h,m);
}

void	initFlight(Flight* pFlight, const AirportManager* pManager)
{	
	char* str;
	getc(stdin);
	setAiport(pManager, &pFlight->pOriginAirport, "Enter code of origin airport:");
	int same;
	do {
		setAiport(pManager, &pFlight->pDestAirport, "Enter code of destination airport:");
		same = isSameAirport(pFlight->pOriginAirport, pFlight->pDestAirport);
		if(same)
			printf("Same origin and destination airport\n");
	} while (same);
	str= getCorrectDate();
	pFlight->date = (Date*)malloc(sizeof(Date));
	initDate(pFlight->date, str);
	pFlight->hour = getFlightHour();
	pFlight->milePerHour = getFlightSpeed();
}

int getFlightHour()
{
	int h;
	do {
		printf("Enter flight hour [0-23]:\t");
		scanf("%d", &h);
	} while (h < 0 || h>23);
	return h;
}

double getFlightSpeed()
{
	double speed;
	do {
		printf("Enter hour and avg speed (mph):\t");
		scanf("%lf", &speed);
	} while (speed < 0);
	return speed;
}

void	setAiport(const AirportManager* pManager, Airport** hAirport, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		myGets(code, MAX_STR_LEN,stdin);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport in this country - try again\n");
	} while(port == NULL);

	*hAirport = port;

}


void	freeFlight(Flight* pFlight)
{
	
	free(pFlight);
}
int comperHour(const void* f1, const void* f2) {

	Flight* a = *(Flight**)f1;
	Flight* b = *(Flight**)f2;
	return a->hour - b->hour;


}
int comperSpeed(const void* f1, const void* f2) {
	Flight* a = *(Flight**)f1;
	Flight* b = *(Flight**)f2;
	return (int)(a->milePerHour - b->milePerHour);


}
int comperDate(const void* f1, const void* f2) {
	Flight* a = *(Flight**)f1;
	Flight* b = *(Flight**)f2;
	if (a->date->year > b->date->year)return 1;
	if(a->date->year < b->date->year)return -1;
	if (a->date->year == b->date->year)
	{
		if (a->date->month > b->date->month)return 1;
			
		if (a->date->month < b->date->month)return -1;
		else {
			if (a->date->day > b->date->day)return 1;
			if (a->date->day < b->date->day)return -1;
		}

	}
	return 0;



}
int SavedatatoFile(Flight* flight, FILE* f) {

	//fwrite(airline->flightArr[i]->pOriginAirport->code, sizeof(char), strlen(airline->flightArr[i]->pOriginAirport->code), fp);
	//	fwrite(airline->flightArr[i]->pDestAirport->code, sizeof(char), strlen(airline->flightArr[i]->pDestAirport->code), fp);
	//	fwrite(&(airline->flightArr[i]->hour), sizeof(int), 1, fp);
	//	fwrite(airline->flightArr[i]->date, sizeof(Date), 1, fp);
	//	fwrite(&(airline->flightArr[i]->milePerHour), sizeof(double), 1, fp);
	
	
	return 1;
}
int ReadatatoFile(Flight* flight, FILE* f) {

	/*fread(flight->pDestAirport, sizeof(Airport), 1, f);
	fread(flight->pOriginAirport, sizeof(Airport), 1, f);
	fread(&flight->hour, sizeof(int), 1, f);
	fread(&flight->date.year, sizeof(Date), 1, f);
	fread(&flight->date.month, sizeof(int), 1, f);
	fread(&flight->date.day, sizeof(int), 1, f);
	fread(&flight->milePerHour, sizeof(double), 1, f);*/
	return 1;
}

void takeOffFlights(Flight* flight, ...)
{
	/*va_list flights=NULL;
	va_start(flights, flight);
	Flight* currentFlight = flight;

	while (currentFlight != NULL)
	{
		printf("\nFlight from \"%s\" to \"%s\" is taking off\n", currentFlight->pOriginAirport->name, currentFlight->pDestAirport->name);
		currentFlight = va_arg(flights, Flight*);
	}

	va_end(flights);*/
}

