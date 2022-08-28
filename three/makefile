# Name: Damandeep Singh
# Course: CS 480
# Account: cssc0953
# A Makefile for Program 3, CS480


PROGRAM = testbbuffer
CC = gcc
CFLAGS = -g -std=c99 

${PROGRAM}:	${PROGRAM}.o bbuffer.o
		${CC} ${CFLAGS} -o ${PROGRAM} ${PROGRAM}.o bbuffer.o -lpthread -lm



clean:
		rm -f *.o ${PROGRAM}

${PROGRAM}.o bbuffer.o: bbuffer.h
