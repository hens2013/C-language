#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "Date.h"


int		addFlight(Company* pComp,const AirportManager* pManager)
{
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount+1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1,sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount],pManager);
	pComp->flightCount++;
	return 1;
}

void	printCompany(Company* pComp)
{
	
	printf("Company %s:\n", pComp->name);
	printf("Has %d planes and %d flights\n", pComp->planeCount, pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH+1];
	char codeDestination[CODE_LENGTH + 1];
	
	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	getc(stdin); //clean buffer
	printf("Origin Airport\n");
	getCode(codeOrigin);
	printf("Destination Airport\n");
	getCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n",codeOrigin, codeDestination);
}

void	initCompany(Company* pComp)
{
	//clean buffer
	fflush(stdin);
	pComp->name = getStrExactName("Enter company name");
	printf("Enter plane count\t");
	scanf("%d", &pComp->planeCount);
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
}

void	deleteCompany(Company* pComp)
{
	free(pComp->name);
	free(pComp->flightArr);
}

void	printFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(pFlight[i]);
}

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
	//generalArrayFunction(arr,size, sizeof(Flight*), freeFlight);
}
void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
}
int initAirportLineFromFile(Company* pCompany, const char* file,AirportManager * pAirportManager) {
	FILE* fp;
	char code[4];
	int size;

	fp = fopen(file, "rb");
	if (!fp)
		return -1;
	fread(&pCompany->planeCount, sizeof(int), 1, fp);
	fread(&size, sizeof(int), 1, fp);
	pCompany->name = (char*)malloc((size + 1) * sizeof(char));
	fread(pCompany->name, sizeof(char), size, fp);
	pCompany->name[size] = '\0';
	fread(&pCompany->flightCount, sizeof(int), 1, fp);
	pCompany->flightArr = (Flight**)malloc(pCompany->flightCount * sizeof(Flight*));
	if (!pCompany->flightArr)
		return -1;
	fread(&(pCompany->sortedtyped), sizeof(sorttype), 1, fp);
	
	for (int i = 0; i < pCompany->flightCount; i++) {
		pCompany->flightArr[i] = (Flight*)malloc(sizeof(Flight));

		fread(code, sizeof(char), 3, fp);
		code[3] = '\0';
		pCompany->flightArr[i]->pOriginAirport = findAirportByCode(pAirportManager, code);

		fread(code, sizeof(char), 3, fp);
		code[3] = '\0';
		pCompany->flightArr[i]->pDestAirport = findAirportByCode(pAirportManager, code);

		fread(&(pCompany->flightArr[i]->hour), sizeof(int), 1, fp);
		pCompany->flightArr[i]->date = (Date*)malloc(sizeof(Date));

		fread(pCompany->flightArr[i]->date, sizeof(Date), 1, fp);

		fread(&(pCompany->flightArr[i]->milePerHour), sizeof(double), 1, fp);
	}

	fclose(fp);
	return 1;
}
int saveAirportLineFromFile(Company* airline, const char* file) {
	FILE* fp;
	int nameSize;
	fp = fopen(file, "wb");
	if (!fp)
		return -1;
	nameSize = (int)strlen(airline->name);
	fwrite(&(airline->planeCount), sizeof(int), 1, fp);
	fwrite(&nameSize, sizeof(int), 1, fp);
	fwrite(airline->name, sizeof(char), nameSize, fp);
	fwrite(&(airline->flightCount), sizeof(int), 1, fp);
	fwrite(&(airline->sortedtyped), sizeof(sorttype), 1, fp);
	for (int i = 0; i < airline->flightCount; i++) {
		fwrite(airline->flightArr[i]->pOriginAirport->code, sizeof(char), strlen(airline->flightArr[i]->pOriginAirport->code), fp);
		fwrite(airline->flightArr[i]->pDestAirport->code, sizeof(char), strlen(airline->flightArr[i]->pDestAirport->code), fp);
		fwrite(&(airline->flightArr[i]->hour), sizeof(int), 1, fp);
		fwrite(airline->flightArr[i]->date, sizeof(Date), 1, fp);
		fwrite(&(airline->flightArr[i]->milePerHour), sizeof(double), 1, fp);
	}
	fclose(fp);
	return 1;

}
void Chosingtypeofsorting(Company* airline) {
	if (airline->flightCount == 0)
	{
		printf("there are no flight yet\n please add in order to sort\n");
		return;
	}
	printf("please enter sorttype\n");
	printf("1 for by hour \n");
	printf("2 for by date \n");
	printf("3 for by speed \n");
	printf("every number for no sorting \n");
	int option = 0;
	scanf("%d", &option);
	switch (option) {
	case 1:
		airline->sortedtyped = Hoursort;
		break;
	case 2:
		airline->sortedtyped = Datesort;
		break;
	case 3:
		airline->sortedtyped = Speedsort;
		break;
	default:
		airline->sortedtyped = none;
		break;


	}
}
void sortingbeforprinting( Company* airline) {
	Chosingtypeofsorting (airline);
	switch (airline->sortedtyped) {

	case Hoursort:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), comperHour);
		break;
	case Datesort:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), comperDate);
		break;
	case Speedsort:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), comperSpeed);
		break;
	case none:
		break;
	}
	
}
void SearchFlight(Company* airline) {
	if (airline->sortedtyped == none)
	{
		printf("sort the flights in the company first\n");
		return;
	}
	int (*compareFunction)(const void*, const void*) = NULL;
	Flight* flightToFind = (Flight*)malloc(sizeof(Flight));
	switch (airline->sortedtyped)
	{
	case Hoursort:
		compareFunction = comperHour;
		printf("Enter hour of flight:\n");
		scanf("%d", &flightToFind->hour);
		break;
	case Datesort:
		compareFunction = comperDate;
		char* str = getCorrectDate();
		flightToFind->date = (Date*)malloc(sizeof(Date));
		initDate(flightToFind->date, str);
		break;
	case Speedsort:
		compareFunction = comperSpeed;
		printf("Enter a speed\n");
		scanf("%lf", &flightToFind->milePerHour);
		break;
	default:
		return;
	}
	Flight** flight = bsearch(&flightToFind, airline->flightArr, airline->flightCount, sizeof(Flight*), compareFunction);
	printFlight(*flight);
	freeFlight(flightToFind);
}


	




