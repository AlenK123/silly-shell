#!/bin/make
#Amit Sarussi sucks

CC = gcc
CFLAGS = -Wall
_OBJ = silly_input.o silly_utils.o linenoise.o
DEPS = silly_input.c silly_utils.c

shell: $(_OBJ) 
	$(CC) -c $(DEPS) $(CFLAGS)
	$(CC) shell.c $(_OBJ) -o $@ $(CFLAGS)
	
.PHONY: all shell clean

clean:
	rm -f *.o
