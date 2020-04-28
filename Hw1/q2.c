#include "q2.h"
#include "general.h"
#include <ctype.h>
#include <stdio.h>
#define COLMS 5
#define ROWS 5

void pictureSquares()
{
	
	int mat[COLMS][ROWS]={{1,1,1,1,0},
					      {1,1,1,1,0},
			    		  {0,0,0,0,1},
						  {1,1,0,0,1},
				 		  {1,1,0,0,1}};
/*int mat[COLMS][ROWS]={{1,2,3,4,5},
					      {6,7,8,9,10},
			    		  {11,12,13,14,15},
						  {16,17,18,19,20},
				 		  {21,22,23,24,25}};
*/
	printf("colms= %d\n",COLMS);
	printf("rows=%d\n",ROWS);
	PrintMat((int*)mat,  ROWS,COLMS);
	printRects((int*) mat);
	


}
//print the rectangles
void printRects(int* mat)
{
int x;
int y;
int width;
int length;

	for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLMS; j++)
			{
				if(*(mat+i*COLMS+j)==1)
				{
				x=j;
				y=i;
				printf("x and y %d %d\n", x,y);		
				findRectWidth((int*)mat,x,y,&width,&length);
				findRectLen((int*)mat,x,y,&width,&length);
				printf(" y(rows): %d , x(colms): %d \n width: %d ,length: %d \n", y,x,width,length);

				}

			}

		}
	



}
//find the width of the rectangle
void findRectWidth(int* mat, int x, int y, int* width, int* length)
{
*width=1;


	mat=mat+y*COLMS+x;
	for (int j = x; j < COLMS-1; j++)
		{
			if(*(mat+1)==1)
			{
				(*width)++;
				*(mat+1)=0;
				mat++;
			}		
			else
			
				break;
					

		}
}
//find the lenght of the rectangle
void findRectLen(int* mat, int x, int y, int* width, int* length)
{
*length=1;

	mat=mat+y*COLMS+x;

	for (int i = y; i < ROWS-1; i++)
	{

		if(*(mat+COLMS)==1)
		{
			(*length)++;

				mat=mat+COLMS;
				for(int j=0; j < *width; j++)
				{
				*(mat)=0;
				mat++;
				}
			
			mat=mat-(*width);

		}
		else
			break;
	}

}









