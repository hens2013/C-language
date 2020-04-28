#include "q3.h"
#include "general.h"
#include <ctype.h>
#include <stdio.h>
#define COLMS 5
#define ROWS 5


void pictureLines()
{
	int rows;
	int colms;
	int mat[COLMS][ROWS];
	int x1,y1,x2,y2;
	int flag=0;
	printf("rows %d, colms %d\n ",ROWS,COLMS);
	// input for the bounding of the matrix
	char* msg="enter please your limits between the range\n";
	matRnC(msg,ROWS,COLMS,&rows,&colms);
	printf("colms= %d\n",colms);
	printf("rows=%d\n",rows);
	createZeroMat((int*) mat, rows, colms);
	PrintMat((int*)mat, rows, colms);
	while(flag==0)
	{
	initLines((int*)mat ,rows, colms,&x1,&y1,&x2,&y2); 
	PrintMat((int*)mat,  rows,  colms);
	printf("please enter 0 to continue , or 1 for exit  \n");
	scanf("%d",&flag);
	}
}
//define the zero mat
void createZeroMat(int* mat, int rows, int colms)
{
for(int i=0;i<rows*colms;i++)
	{
		*mat=0;
		mat++;
	}

}
//input line method
void initLines(int* mat,int rows, int colms,int* x1,int* y1,int* x2,int* y2)
{

int answer=0;
int count=0;
int a1=0,a2=0,a3=0;
do{
printf("please enter your line\n");
	scanf("%d",x1);
	scanf("%d",y1);
	scanf("%d",x2);
	scanf("%d",y2);
	answer=checkLines(rows, colms,*x1,*y1,*x2,*y2);
}while(answer!=1);
	
	
	if(answer==1)
	{	//if the line horizental 
		if(*x1==*x2)
		{
		//checking around the line if there are another lines around	
		a1=checkLegalityV((int*)mat,rows, colms,*x1,*y1,*x2,*y2);
			
			if(*x1+1<colms){
				a2=checkLegalityV((int*)mat,rows, colms,*x1+1,*y1,*x2,*y2);
				
				}
			if(*x1-1>=0){			
				a3=checkLegalityV((int*)mat,rows, colms,*x1-1,*y1,*x2,*y2);
				
				}
			count=a1+a2+a3;	
			if(count!=0)
				printf("the line is not invalid\n");
			else
				addLine((int*)mat,rows, colms,*x1,*y1,*x2,*y2);	
		}
		//vertical line
		else
		{	//checking around the line if there are another lines around	
			a1=checkLegalityH((int*)mat,rows, colms,*x1,*y1,*x2,*y2);
			
			if(*y1+1<rows){
				a2=checkLegalityH((int*)mat,rows, colms,*x1,*y1+1,*x2,*y2);
				
				}
			if(*y1-1>=0){		
				a3=checkLegalityH((int*)mat,rows, colms,*x1,*y1-1,*x2,*y2);
				
				}
			count=a1+a2+a3;	
			if(count!=0)
				printf("the line is not invalid\n");
			else 
				addLine((int*)mat,rows, colms,*x1,*y1,*x2,*y2);
				
		}

	}

}
// add the line to the mat
void addLine(int* mat,int rows, int colms,int x1,int y1,int x2,int y2)
{
	mat=mat+y1*colms+x1;
	if(y1==y2)
	{
		
		for(int i=x1;i<=x2;i++)
		{
			*mat=1;
			mat++;
			
		}
	}
	else
	{
		for(int i=y1;i<=y2;i++)
			{
				*mat=1;
				mat=mat+colms;
				
			}
	}

}


// check for vertical line
int checkLegalityV(int* mat ,int rows, int colms,int x1,int y1,int x2,int y2)
{
	mat=mat+y1*colms+x1;
	if((y1>0)&&(*(mat-colms)==1))
		return 1;
	
	for (int i=y1; i<=y2+1; i++)
	{
	if(*mat==1)
		return 1;
	mat=mat+colms;
	}

	if((y2+1>rows)&&(*(mat+colms)==1))
		return 1;	
	

	return 0;
}	
// check for horizontal line
int checkLegalityH(int* mat,int rows, int colms,int x1,int y1,int x2,int y2)
{
	mat=mat+y1*colms+x1;
	if((x1>0)&&(*(mat-1)==1))
		return 1;	
	
	for (int i=x1; i<=x2; i++)
	{
	if(*mat==1)
		return 1;
	mat++;
	}
	
	if((x2+1<colms)&&(*(mat+1)==1))
		return 1;

return 0;
}	

//return 1 for vaild 0 for not valid
int checkLines(int rows, int colms,int x1,int y1,int x2,int y2)
{
	
	if((x1>=colms)||(x1<0))
		return 0;
	if((x2>=colms)||(x2<0))
		return 0;
	if((y1>=rows)||(y1<0))
		return 0;
	if((y2>=rows)||(y2<0))
		return 0;
	if((x1>x2)|| (y1>y2))
		return 0;
	if((x1==x2) && (y1!=y2))
		return 1;
	if((x1!=x2) && (y1==y2))
		return 1;

return 0;
}



