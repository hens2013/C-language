#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "Date.h"



void printDate(const Date* date) 
{
	printf("Date: %2d/%2d/%2d\n", date->day, date->month, date->year);
	
}

void initDate(Date* pDate, char* str) {
	sscanf(str, "%d/%d/%d", &pDate->day, &pDate->month, &pDate->year);
}