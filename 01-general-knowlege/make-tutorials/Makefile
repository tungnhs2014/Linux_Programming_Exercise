.PHONY: hello hellomake

CC:= gcc
CFLAG:= -I.

INC_FILES := hello.h


hellomake: main.o hello.o
	$(CC) -o $@ main.o hello.o $(CFLAG)

hello:
	gcc hello.c main.c -o hello -I.

clean:
	rm -rf hello hellomake *.o
	
