#ifndef __FLIGHT__
#define __FLIGHT__

#include "Airport.h"
#include "AirportManager.h"
#include "Date.h"
typedef struct
{
	Airport*	pOriginAirport;
	Airport*	pDestAirport;
	int			hour;
	Date*		date; //dd/mm/yyyy
	double		milePerHour;
}Flight;

int		isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, const char* codeDest);
double	flightTime(const Flight* pFlight);
void	printFlight(const Flight* pFlight);
void	initFlight(Flight* pFlight,const AirportManager* pManager);
int		getFlightHour();
double	getFlightSpeed();
void	setAiport(const AirportManager* pManager,Airport** hAirport, const char* msg);

void	freeFlight(Flight* pFlight);
int comperHour(const void* f1, const void* f2);
int comperDate(const void* f1, const void* f2);
int comperSpeed(const void* f1, const void* f2);
int ReadatatoFile(Flight* flight, FILE* f);
void takeOffFlights(Flight* flight, ...);
#endif
