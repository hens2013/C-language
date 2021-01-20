CC=gcc
OBJS= q1.o general.o 
EXEC=histogram1 
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)  #if you have CFLAGS you do not have to write for each file $(CC) -c $*.c!!!

$(EXEC) : $(OBJS)
	
	$(CC) $(OBJS) -lpthread -o$@


q1.o: q1.c general.h
general.o: general.h

clean: 
	rm -f $(EXEC) $(OBJS)




