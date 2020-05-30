#pragma once
typedef struct
{
	int day;
	int month;
	int year;
}Date;

void printDate(const Date* date);
void initDate(Date* pDate, char* str);