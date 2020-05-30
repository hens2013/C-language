#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"
#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	do {
		printf("How many airport?\t");
		scanf("%d", &pManager->count);
	} while (pManager->count < 1);

	pManager->arr = (Airport*)malloc(pManager->count * sizeof(Airport));
	if (!pManager->arr)
		return 0;

	
	for (int i = 0; i < pManager->count; i++)
	{
		
		createAirport(pManager->arr, i);
	}
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return 1;
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	for (int i = 0; i < pManager->count; i++)
	{
		if (isAirportCode(&pManager->arr[i], code))
			return &pManager->arr[i];
	}
	return NULL;
}

void	printAllAirport(const AirportManager* pManager)
{
	generalArrayFunction(pManager->arr, pManager->count, sizeof(Airport), printAirport);
	
}



void  createAirport(Airport* arr, int index)
{
	//clean buffer
	char tav;
	scanf("%c", &tav);
	while(1)
	{
		initAirportCode(&arr[index]);
		if (checkUniqeCode(arr[index].code, arr, index))
			break;

		printf("This code already in use - enter a different code\n");
	}
	
	initAirportNoCode(&arr[index]);

}

int	addAirport(AirportManager* pManager)
{
	pManager->arr = (Airport*)realloc(pManager->arr, (pManager->count + 1) * sizeof(Airport));
	if (!pManager->arr)
		return 0;

	createAirport(pManager->arr, pManager->count);
	pManager->count++;
	return 1;
}



void freeManager(AirportManager* pManager)
{
	generalArrayFunction(pManager->arr, pManager->count, sizeof(Airport), freeAirport);
}

int initAirportManagerFromFile(AirportManager* pManager, const char* filename) {
	FILE* f = fopen(filename, "r");


	pManager->arr = NULL;
	pManager->count = 0;
	if (f == NULL) return 0;
	int count = 0;
	fscanf(f, "%d", &count);
	pManager->count = count;
	pManager->arr = (Airport*)malloc(sizeof(Airport) * count);
	for (int i = 0; i < count; i++)
	{
		Airport a;
		readAirportDataFromFile(&a, f);
		pManager->arr[i] = a;
	}
	fclose(f);
	return 1;
}
int saveDataTofile(AirportManager* pManager, const char* filename)
{
	FILE* f = fopen(filename, "w");
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return 0;
	}
	fprintf(f, "%d\n", pManager->count);
	for (int i = 0; i < pManager->count; i++)
	{
		Airport a = pManager->arr[i];
		saveAirportDataFromFile(&(a), f);
		
	}
	fclose(f);

	return 1;






}




