#include "q1.h"
#include "general.h"
#include <ctype.h>
#include <stdio.h>
#define COLMS 5
#define ROWS 7
void findMaxSubMatrix()
{

	printf("colms= %d",COLMS);
	printf("\n");
	printf("rows=%d",ROWS);
	printf("\n");
	int min=5;
	int max=10;
	int mat[COLMS][ROWS];
	int rows;
	int colms;
	int subRow;
	int subColm;

	char* msg="enter please your limits between the range\n";
	matRnC(msg,ROWS,COLMS,&rows,&colms);
	
	//create the big matrix and print
	createMat((int*) mat, rows, colms,min,max);

	char* msg2="enter please the little mat range\n";
	matRnC(msg2,rows,colms,&subRow,&subColm);
	
	maxSumMat((int*) mat, rows, colms, subRow, subColm);

	

}
void findSnP(int* mat, int rows, int colms,int subRow,int subColm,int* sumMinMat, int* maxRow, int* maxColm)
{
int temp;
*sumMinMat=matSum((int*)mat,subRow,subColm,rows,colms);
*maxRow=0;
*maxColm=0;
for (int i = 0; i <= rows-subRow; i++)
	{
		for (int j = 0; j <= colms-subColm; j++)
		{
			
			//printf(" first num  of min matrix %d\n", *mat);
			temp=matSum((int*)mat,subRow,subColm,rows,colms);
			printf("sum %d\n" , temp);
			if((*sumMinMat)<temp)
			{
				*maxRow=i;
				*maxColm=j;	
				(*sumMinMat)=temp;
				
			}
			
		
			mat++;
		}

	mat=mat+subColm-1;
	
	}




}
void PrintMinMat(const int* mat, int subRow,int subColm,int* startR, int* startC, int colms)
{
	int i, j;

	for (i = *startR; i < subRow+(*startR); i++)
	{
		for (j = *startC; j <subColm+(*startC); j++)
		{
			
				mat=mat+i*colms+j;
				printf("%5d", *mat);
				//return to original adrres
				mat=mat-(i*colms+j);
		}
		printf("\n");

	}
	printf("\n");
}
//find little mat sum
int matSum(const int* mat, int rows, int colms,int rowBig, int colmBig)
{
int i, j;
int sum=0;

	
for (i = 0; i <rows; i++)
	{
		for (j = 0; j <colms; j++)
		{	
		//printf("the num now %d \n",*mat);
			sum=sum+(*mat);
			mat++;		
		//	printf("s=%d\n",sum);
		}
	mat=mat+colmBig-colms;	
	}

return sum;
}



void maxSumMat(int* mat, int rows, int colms,int subRow, int subColm)
{

	int sumMinMat;
	int maxRow;
	int maxColm;

	findSnP((int*)mat, rows, colms, subRow, subColm, &sumMinMat,&maxRow,&maxColm);
	//printf("r=%d c=%d\n",maxRow,maxColm);-print x,y
	
	PrintMat((int*)mat,  rows,  colms);
	printf("\n");

	
	PrintMinMat((int*)mat,subRow,subColm,&maxRow,&maxColm,colms );

	printf("\n");
	printf("the max sum is %d\n",sumMinMat);
}
