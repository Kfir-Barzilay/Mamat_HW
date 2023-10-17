CC=g++
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c++11
OBJS= ip.o port.o string.o
LIBS= -linput -lfirewall -L.
EXEC = firewall.exe

$(EXEC): $(OBJS) main.o libfirewall.so
	$(CCLINK) $(CFLAGS) main.o -o $(EXEC)  $(LIBS)

libfirewall.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o libfirewall.so $(LIBS)

main.o: main.cpp ip.h port.h string.h generic-field.h
	$(CC) $(CFLAGS) -c -fpic main.cpp

ip.o: string.h ip.h ip.cpp generic-field.h
	$(CC) $(CFLAGS) -c -fpic ip.cpp

port.o: string.h port.h port.cpp generic-field.h
	$(CC) $(CFLAGS) -c -fpic port.cpp

string.o: string.h string.cpp
	$(CC) $(CFLAGS) -c -fpic string.cpp

clean:
	rm -rf *.o firewall.exe libfirewall.so
