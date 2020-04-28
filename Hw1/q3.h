#ifndef	Q3_H_
#define Q3_H_

void pictureLines();
void createZeroMat(int* mat, int rows, int colms);
int checkLines(int rows, int colms,int x1,int y1,int x2,int y2); 
void initLines(int* mat,int rows, int colms,int* x1,int* y1,int* x2,int* y2);
int checkLegalityH(int* mat ,int rows, int colms,int x1,int y1,int x2,int y2); 
int checkLegalityV(int* mat ,int rows, int colms,int x1,int y1,int x2,int y2); 
void addLine(int* mat,int rows, int colms,int x1,int y1,int x2,int y2);
#endif


	
