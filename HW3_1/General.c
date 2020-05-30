#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Date.h"
#include "General.h"
#define TEMP_BUFFER_SIZE 50

char* getStrExactstrfromFile( FILE* f)
{

	char* str;
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN,f);
	str = getDynStr(temp);
	printf("the str is %s\n", str);
	return str;
}

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN,stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}


char* getCorrectDate()
{

	char* str;
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		puts("Enter Flight Date dd/mm/yyyy\t");
		myGetsdate(date, MAX_STR_LEN);
		ok = checkDate(date);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);

	str = (char*)malloc((strlen(date) + 1) * sizeof(char));
	if (!str)
		return NULL;

	strcpy(str, date);
	return str;
}
const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int	 checkDate(char* date)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;

	sscanf(date, "%d/%d/%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	
	return 1;
}


double getDoubleCheckLimits(const char* msg, double start, double end)
{
	double val;
	do {
		printf("%s number should be between %.2lf and %.2lf including\n", msg, start, end);
		scanf("%lf", &val);
		if (val < start || val > end)
			printf("error in number, try again\n");
	} while (val < start || val > end);

	return val;
}


void generalArrayFunction(void* arr, int length, int size, void (*f)(void*))
{
	int i;
	for (i = 0; i < length; i++)
		f((char*)arr + i * size);
}

char* getStrExactLength(FILE* source)
{
	char temp[TEMP_BUFFER_SIZE]; 
	myGets(temp, TEMP_BUFFER_SIZE, source);
	
	return strdup(temp);
	
}
char* myGets(char* buffer, int size, FILE* f)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, f))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		*buffer = '\0';
	}
	return NULL;
}

char* myGetsdate(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}