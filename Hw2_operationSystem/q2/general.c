#include "general.h"
#include <stdlib.h>  
#include <stdio.h> 
//get the numbers from the file
int * getNumbersFromFile(int * size,char * name)
{
	
	FILE * fp;
	fp=fopen(name,"r");
	if(fp==NULL)
	{
		printf("error\n");
		return NULL;
	}
	fscanf(fp,"%d",size);
	int * arr=(int*)malloc(sizeof(int)*(*size));
	for(int i=0;i<*size; i++)
	{
	fscanf(fp,"%d",&arr[i]);
	}
	fclose(fp);
	return arr;


}







void printArr(int *arr)
{	int index1=1,index2=10;
	for(int i=0;i<10; i++)
	{
		if(arr[i]==0)
		{
		index1+=10;
		index2+=10;
		continue;
		}
		else
		printf("%d-%d: %d\n",index1,index2,arr[i]);
		index1+=10;
		index2+=10;
	}
}


void zeroArr(int * arr)
{
	for(int a=0;a <10; a++)
	{	
		arr[a]=0;
	}
}

int * bigArray(int *arrc1,int * arrc2)
{
	int * arrp=(int*)malloc(sizeof(int)*10);
	zeroArr(arrp);
	for(int i=0;i<10; i++)
		arrp[i]=arrc1[i]+arrc2[i];
	return arrp;

}



