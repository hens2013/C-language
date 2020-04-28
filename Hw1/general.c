#include "general.h"
#include "q1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitMat(int* mat, int rows, int colms, int min, int max)
{
	
	
	for(int i=0;i<rows*colms;i++)
	{
		*mat = min+(rand() %(max-min+ 1)) ;
		mat++;
	}
	
}
//cheaking user input
void matRnC(const char* massage ,int rowBig, int colmBig, int* rows, int* colms){
int flag=0;
	printf("%s",massage);
while(flag==0)
{
	
		scanf("%d",colms);
		scanf("%d",rows);
	
	if((colmBig>=*colms)&&(rowBig>=*rows))
		flag=1;
	else
	printf("enter colms and rows again \n");
}
return;	
}



void PrintMat(const int* mat, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%5d", *mat);
			mat++;
		}
		printf("\n");
	}
	printf("\n");
}

void createMat(int* mat, int rows, int colms,int min, int max)
{
		InitMat((int*)mat, rows, colms,min,max);
		PrintMat((int*)mat,rows, colms);

}







