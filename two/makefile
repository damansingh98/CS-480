# Name: Damandeep Singh
# Account: cssc0953
# Course: CS480-02
# A Makefile for Program 2, CS480


PROGRAM =testmulthreads
CC = gcc
CFLAGS = -g -std=c99 

${PROGRAM}:	${PROGRAM}.o specialcountmulthreads.o
		${CC} ${CFLAGS} -o ${PROGRAM} ${PROGRAM}.o specialcountmulthreads.o -lpthread -lm

specialcountmulthreads.o ${PROGRAM}.o:	count.h


clean:
		rm -f *.o ${PROGRAM}		
