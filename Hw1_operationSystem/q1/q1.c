
#include "general.h" 
#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#define READ 0
#define WRITE 1


//created byBar Zada and Hen Shiryon

int main(int argc,char * argv[])
{

	

			


int pipe1[2];	
int pipe2[2];
int pipe3[2];
int fd=dup(STDOUT_FILENO);
	pid_t child1;
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
	int sizeParent=0;
	
	
	//creating pipe and check error
	int r=pipe(pipe1);
	int r2=pipe(pipe2);
	int r3=pipe(pipe3);
	if(r==-1||r2==-1|| r3==-1){
		perror("pipe");
		exit(1);
	}

	
	//create kids and check error
	 child1=fork();
	if(child1<0)
	{
	perror("fork");
	exit(1);
	}

	//child1 process
	if(child1==0)
	{
			close(pipe1[WRITE]);
			if(dup2(pipe1[READ],STDIN_FILENO)==-1)
			{
			perror("dup");
			exit(1);
			
			}
			if(read(STDIN_FILENO,&sizeParent,sizeof(int))==-1)
			{
			perror("fork");
			exit(1);
			}
			
			int arrParent[sizeParent];
			
			if(read(pipe1[READ],arrParent,sizeof(int)*sizeParent)==-1)
		
			{
			perror("fork");
			exit(1);
			}

			
			int * arrchild1=getHistogramchild(arrParent, sizeParent);
			
			if(dup2(pipe3[WRITE],STDOUT_FILENO)==-1)
			{	
			perror("dup2");
			exit(1);
			
			}
			
			if(write(STDOUT_FILENO,arrchild1,10*sizeof(int))==-1)
			{
			perror("write");
			exit(1);
			
			}
			close(pipe1[READ]);
		
			free(arrchild1);

   	  
	}
	else if(child1>0)
		{
			pid_t child2=fork();
			if(child2==0)
			{
			close(pipe2[WRITE]);
			if(dup2(pipe2[READ],STDIN_FILENO)==-1)
			{
			perror("dup");
			exit(1);
			
			}
			if(read(STDIN_FILENO,&sizeParent,sizeof(int))==-1)
			{
			perror("fork");
			exit(1);
			}
			
			int arrParent[sizeParent];
			int n=read(pipe2[READ],arrParent,sizeof(int)*sizeParent);
			
			
			
			int * arrchild2=getHistogramchild(arrParent, n/sizeof(int));
			
			
			close(pipe3[READ]);			
			if(dup2(pipe3[WRITE],STDOUT_FILENO)==-1)
			{
			perror("dup");
			exit(1);
			
			}
			if(write(STDOUT_FILENO,arrchild2,10*sizeof(int))==-1)

			{
			perror("write");
			exit(1);
			
			}
			close(pipe2[READ]);
			free(arrchild2);
		
			
			}
		else if(child2>0)
			{
			//parent process

			//get the numbers from the file

			int * arrParent=getNumbersFromFile(&sizeParent,argv[1]);
			
	
			int *c1=spiltArray(0,sizeParent/2,arrParent);
			int *c2=spiltArray(sizeParent/2,sizeParent,arrParent);
			//write the array to the childs
			//child1
			dup2(pipe1[WRITE],STDOUT_FILENO);
			int size1=sizeParent/2;
			if(write(STDOUT_FILENO,&size1,sizeof(int))==-1)
			{
			perror("write");
			exit(1);
			
			}
			if(write(STDOUT_FILENO,c1,sizeof(int)*size1)==-1)
			{
			perror("write");
			exit(1);
			
			}
			
			//child2
			int size2=sizeParent-size1;
			if(dup2(pipe2[WRITE],STDOUT_FILENO)==-1)
			{
			perror("dup");
			exit(1);
			
			}
			
			if(write(STDOUT_FILENO,&size2,sizeof(int))==-1)
			{
			perror("write");
			exit(1);
			
			}
			if(write(STDOUT_FILENO,c2,sizeof(int)*size2)==-1)
			{
			perror("write");
			exit(1);
			
			}
			
			
			for(int i=0;i<2; i++)
			wait(NULL);		
		
	
			//get the data from the childs
			int arrchild1[10];
			int arrchild2[10];	
			if(dup2(pipe3[READ],STDIN_FILENO)==-1)
			{
			perror("write");
			exit(1);
			
			}
			if(read(STDIN_FILENO,arrchild1,10*sizeof(int))==-1)
			{
			perror("fork");
			exit(1);
			}
			
			
		
			if(read(STDIN_FILENO,arrchild2,10*sizeof(int))==-1)
			{
			perror("fork");
			exit(1);
			}
			
			//get the hisogram
			int * bighistogram=bigArray(arrchild1,arrchild2);
			
			if(dup2(fd,STDOUT_FILENO)==-1)
			{
			perror("write");
			exit(1);
			
			}
			
			printArr(bighistogram);
 			free(arrParent);	
    			free(bighistogram);
		
			}
			
			
				
				
			

		
		
		
			}
		else
		{
			
			perror("fork");
			exit(1);
			
			
		}	
		
		
	
			
	


	
	

	 
			
    return 0;






}

