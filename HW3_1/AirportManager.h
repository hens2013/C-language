#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__
#include <stdio.h>

#include "Airport.h"

typedef struct
{
	Airport*	arr;
	int			count;
}AirportManager;

int		 addAirport(AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
void	printAllAirport(const AirportManager* pManager);
int		initManager(AirportManager* pManager);
void	freeManager(AirportManager* pManager);

void	createAirport(Airport* arr, int index);

int initAirportManagerFromFile(AirportManager* pManager, const char* filename);
int saveDataTofile(AirportManager* pManager, const char* filename);
#endif