CC=gcc
OBJS=general.o main.o q1.o q2.o q3.o
EXEC=HW1
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)  #if you have CFLAGS you do not have to write for each file $(CC) -c $*.c!!!

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@


general.o: general.c general.h q1.h
main.o: main.c q1.h general.h q2.h
q1.o: q1.c q1.h general.h
q2.o: q2.c q2.h general.h
q3.o: q3.c q3.h general.h



clean: 
	rm -f $(EXEC) $(OBJS)




