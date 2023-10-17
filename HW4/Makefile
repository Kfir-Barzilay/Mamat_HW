CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=grades.o 

libgrades.so: $(OBJS) grades.c grades.h linked-list.h
	$(CCLINK) -shared $(OBJS) -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC)  $(CFLAGS) -c -fpic grades.c

clean:
	rm -rf *.o 