#include "q1.h"
#include "general.h"
#include "q2.h"
#include "q3.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define BIG_SUM 1
#define SQUARE 2
#define LINES 3
#define EXIT -1

//created byBar Zada and Hen Shiryon

int menu();
int main()
{

int option;
int stop = 0;
srand((unsigned)time(NULL));
do
{
	option = menu();
	switch(option)
{
	 case BIG_SUM:
		findMaxSubMatrix();
		break;
	case SQUARE:
		pictureSquares();
		break;
	case LINES:
		pictureLines();
		break;
	case EXIT:
		printf("Bye bye\n");
		stop = 1;
		break;
	default:
		printf("Wrong option\n");
		break;
		}
}while(!stop);
	return 1;
}
int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	printf("%d -Biggest Matrix Sum\n", BIG_SUM);
	printf("%d -Squares\n",SQUARE);
	printf("%d -Lines\n",LINES);
	printf("%d -Quit\n",EXIT);
	scanf("%d", &option);
	return option;

}
