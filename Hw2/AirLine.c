/*
 * AirLine.c
 *
 *  Created on: 7 May 2020
 *      Author: hen
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "AirLine.h"
#include "Flight.h"
#include "AirportManager.h"
#include "general.h"
#include "Airport.h"
int initAirline(Airline* al){
	al->name=getStrExactLength();
	al->numofAirplanes=NumberPosistive();
	al->numofFlights=0;
	al->flights=(Flight**)malloc(sizeof(Flight*)*al->numofFlights);
	addingFlight(al);
	if(!addingFlight(al)||!al->name||!al->numofAirplanes)
		return 0;
return 1;
}
int addingFlight(Airline* al){
	Flight* c;
	initFlight(c);
	if(!initFlight(c))
		return 0;
	al->flights=(Flight**)malloc(sizeof(Flight*)*al->numofFlights+1);
	al->flights[al->numofFlights]=c;
	al->numofFlights++;
return 1;


}

void printAirline(const Airline* al){
	printf("Airline:\n");
	printf("Name:%s",al->name);
	printf("\n numofAirplanes:%d",al->numofAirplanes);
	printf("\n numofFlights:%d",al->numofFlights);
	for (int var = 0; var < al->numofFlights; ++var) {
		printFlight(al->flights[var]);

	}



}
void FreeAirline(Airline* al){
	free(al->name);
	for (int var = 0; var < al->numofFlights; ++var) {
		free(al->flights[var]);
	}
	free(al->flights);


}

int countFlightLines(const Airline* al);

