CC=gcc
EXEC=Histogram2
CFLAGS=-std=c99 -Wall -Werror
	
Histogram2: parent.o child.o general.o
	
	gcc child.c  general.c -o child
	gcc parent.c general.c -o Histogram2



child.o: child.c general.h
general.o: general.c general.h
parent.o: parent.c general.h

	

