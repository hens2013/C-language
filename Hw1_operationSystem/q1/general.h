#ifndef	GENERAL_H_
#define GENERAL_H_

// fun for getting the numbers in 1-50 range
void getHistogram(int **arr,int *arrchild, int sizeparent, int sizechild);

// fun for getting the numbers in 51-100 range
int* getHistogramchild(int *arr, int sizeparent);

//get the numbers from the file
int * getNumbersFromFile(int * size,char * name);



//print the array
void printArr(int *arr);

//big histogram
int * bigArray(int *arrc1,int * arrc2);

void zeroArr(int * arr);



int * spiltArray(int start,int end, int * arr);
#endif
