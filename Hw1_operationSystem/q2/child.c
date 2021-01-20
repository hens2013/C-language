
#include "general.h" 
#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 



int main()
{
	
	
	int sizeArr=0;
	
	
	read(STDIN_FILENO,&sizeArr,sizeof(int));
	int* arrParent=(int*)malloc(sizeof(int)*sizeArr);
	read(STDIN_FILENO,arrParent,sizeof(int)*sizeArr);
	int * arrchild=getHistogramchild(arrParent, sizeArr);	
	write(STDOUT_FILENO,arrchild,sizeof(int)*10);
	free(arrchild);
	free(arrParent);

	
	
	


}
	
