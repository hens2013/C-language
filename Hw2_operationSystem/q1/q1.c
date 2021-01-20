

#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#include "general.h" 

//created byBar Zada and Hen Shiryon



int main(int argc,char * argv[])
{

	const int NTHREADS=2;

			

int fd=dup(STDOUT_FILENO);
	//int status;
	if(argc<2)
	{
		printf("Missing FileName\n");
		return 1;
	}
	else
	{	
		
		printf("file name:%s\n",argv[1]);
	}	
	
	int size=0;
	//reading the numbers from the text file
	int * ar=getNumbersFromFile(&size,argv[1]);
	pthread_t Hisogramthreads[NTHREADS];
	Subarray sb1,sb2;
	//zeroArr((int*)ar);
	int arH[10];	
	zeroArr((int*)arH);

	//create the threads
	//thread1
	sb1.ar=&ar[0];
	sb1.n=size/2;
	sb1.arrHistogram=arH;
	sb1.sizeHistogramArr=10;

	if((pthread_create(&Hisogramthreads[0],NULL,getHistogramFromThreads,(void*)&sb1))!=0)
	{
		perror("join");
		exit(1);
	}

	//thread2
	sb2.ar=&ar[sb1.n];
	sb2.n=size-sb1.n;
	sb2.arrHistogram=arH;
	sb2.sizeHistogramArr=10;
	if((pthread_create(&Hisogramthreads[1],NULL,getHistogramFromThreads,(void*)&sb2))!=0)
	{
		perror("join");
		exit(1);
	}
	
	int *halfArray1=NULL;
	int *halfArray2=NULL;
	//main thread join to the others threads
	if(pthread_join(Hisogramthreads[0],(void**)&halfArray1)!=0)
	{

		perror("join");
		exit(1);
	}
	
	if(pthread_join(Hisogramthreads[1],(void**)&halfArray2)!=0)
	{
		perror("join");
		exit(1);
	}
		
		
	int * fullArr3= bigArray((int*)halfArray1,(int *) halfArray2);
	
	//display the historgram
 	

		if(dup2(fd,STDOUT_FILENO)==-1)
			{
			perror("write");
			exit(1);
			
			}


			
	
	printArr((int*)fullArr3);		
	


	free(halfArray1);
	free(halfArray2);
	free(fullArr3);
    return 0;






}





