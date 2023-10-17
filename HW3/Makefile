# Variables
CC = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = $(CC)
RM = rm -rf
EXEC = prog.exe
OBJS = main.o stack.o student.o

# Phony targets
.PHONY: all clean

# Default target
all: $(EXEC)

# Compile main file
main.o: main.c stack.h student.h
	$(CC) $(CFLAGS) -c main.c

# Compile stack file
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

# Compile student file
student.o: student.c student.h stack.h
	$(CC) $(CFLAGS) -c student.c

# Link object files
$(EXEC): $(OBJS)
	$(CCLINK) -o $(EXEC) $(OBJS)

# Clean object files and executable
clean:
	$(RM) $(OBJS) $(EXEC)
