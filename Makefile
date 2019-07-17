# -*- Makefile -*-
CC= gcc
CFLAGS= -Wvla -std=c99 -Wextra -g -DNDEBUG -Wall -c

#All Target

all: MyString.a

#Executeabla File

MyString.a: MyString.o
	ar rcs MyString.a MyString.o

BuggyLinkedList: BuggyLinkedList.o
	$(CC) BuggyLinkedList.o -o BuggyLinkedList

#Object BuggyLinkedList and MyString
BuggyLinkedList.o: BuggyLinkedList.c
	$(CC) $(CFLAGS) BuggyLinkedList.c -o BuggyLinkedList.o

MyString.o: MyString.c
	$(CC) $(CFLAGS) MyString.c -o MyString.o

#Other Traget
clean:
	-rm -f *.o
	-rm MyString.a

.PHONY: clean
