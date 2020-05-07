/*
 * AirLine.h
 *
 *  Created on: 7 May 2020
 *      Author: hen
 */

#ifndef AIRLINE_H_
#define AIRLINE_H_
#include "Flight.h"
typedef struct{

	char* name;
	int numofAirplanes;
	int numofFlights;
	Flight** flights;

}Airline;

int initAirline(Airline* al);
void printAirline(const Airline* al);
void FreeAirline(Airline* al);
int addingFlight(Airline* al);
int countFlightLines(const Airline* al);



#endif /* AIRLINE_H_ */
