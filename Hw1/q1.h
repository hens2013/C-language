#ifndef	Q1_H_
#define Q1_H_


void findSnP(int* mat, int rows, int colms,int subRow,int subColm,int* sumMinMat, int* maxRow, int* maxColm);
void findMaxSubMatrix();
int matSum(const int* mat, int rows, int colms,int rowBig, int colmBig);
void PrintMinMat(const int* mat, int subRow,int subColm,int* startR, int* startC, int colms);

void maxSumMat(int* mat, int rows, int colms,int subRow, int subColm);


#endif
