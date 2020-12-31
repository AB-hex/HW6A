# define CC, CCLINK, CFLAGS, and OBJS
CC=gcc
CCLINK=$(CC) 
CFLAGS=-g -Wall -std=c99
OBJS=ransom.o

# The first rule is invoked by default.
# We can also invoke it (or any other rule) manually with "make all" - 

prog.exe: $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe

# rules
ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c

# "make clean"

clean:
	rm -rf *.o *.exe
