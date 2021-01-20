

#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#include <errno.h> 
#include "general.h" 

//created byBar Zada and Hen Shiryon

void * getHistogramFromThreads(void * subarray);



pthread_mutex_t mutexHistogram=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

int count=0;


int location=0;
const int CHUNKSIZE=5;

void*  getHistogramFromThreads(void * subarray)
{
	
	
	//int * arr=(int*)malloc(10*sizeof(int));
	

	int index1=1,index2=10;
	
	int temp=CHUNKSIZE+location;
	for(int i=location;i <temp; i++)
	{
		location++;
		if(pthread_mutex_lock(&mutexHistogram)!=0)
			{

				perror("pthread_mutex_lock\n");
			}
		for(int j=0;j<10; j++)
		{	
			
			
			if(((Subarray*) subarray)->ar[i]>=index1 && ((Subarray*) subarray)->ar[i]<=index2)
			{

				((Subarray*) subarray)->arrHistogram[j]+=1;
					
				
				break;
			}
				
			
			index1+=10;
			index2+=10;
			
		}
		if(pthread_mutex_unlock(&mutexHistogram)!=0)
				perror("pthread_mutex_unlock\n");
		index1=1;
		index2=10;
		
		
		
	}	

		
	sleep(1);
	
		
	if(pthread_mutex_lock(&mutexHistogram)!=0)
		perror("pthread_mutex_lock\n");
	
	count++;
	
	if(pthread_mutex_unlock(&mutexHistogram)!=0)
			perror("pthread_mutex_unlock\n");
	if(pthread_cond_signal(&cond)!=0)
	
	perror("pthread_cond_signal\n");
	return NULL;

	

}



int main(int argc,char * argv[])
{


	
	if(pthread_mutex_init(&mutexHistogram,NULL)!=0)
	{
	perror("pthread_mutex_init\n");
	}
	
	if(pthread_cond_init(&cond,NULL)!=0)
	{
	perror("pthread_cond_init\n");
	}

	
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
	Subarray sb1;
	//zeroArr((int*)ar);
	int arH[10];	
	zeroArr((int*)arH);

	//create the threads
	//thread1
	sb1.ar=&ar[0];
	sb1.n=size;
	sb1.arrHistogram=arH;
	sb1.sizeHistogramArr=10;
	

	if((pthread_create(&Hisogramthreads[0],NULL,getHistogramFromThreads,(void*)&sb1))!=0)
	{
		perror("pthread_create");
		exit(1);
	}

	
	
	if((pthread_create(&Hisogramthreads[1],NULL,getHistogramFromThreads,(void*)&sb1))!=0)
	{
		perror("pthread_create");
		exit(1);
	}
	



	
	
	
	//display the historgram
 	

		if(dup2(fd,STDOUT_FILENO)==-1)
			{
			perror("write");
			exit(1);
			
			}

	
	if(count<2)
{
	
	while(count<2)
	{
		if(pthread_cond_wait(&cond,&mutexHistogram)!=0)
		perror("pthread_cond_wait\n");

		printf("wait for signal = %d\n",count);
	
	
	}
}
		
	printf("the arr histogram is:\n");
	printArr((int*)(sb1.arrHistogram));		
	
	
	if(pthread_join(Hisogramthreads[0],NULL)!=0)
	{

		perror("join");
		exit(1);
	}
	
	if(pthread_join(Hisogramthreads[1],NULL)!=0)
	{
		perror("join");
		exit(1);
	}
	
	if(pthread_mutex_destroy(&mutexHistogram)!=0)
		perror("pthread_mutex_destroy\n");
	if(pthread_cond_destroy(&cond)!=0)
	perror("pthread_cond_destroy\n");
	
	

	
    return 0;






}



