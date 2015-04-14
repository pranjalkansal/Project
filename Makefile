#**********************
#*
#* Progam Name: Grade Calculator.
#*
#* Current file: Makefile
#* About this file: Build Script.
#* 
#***********************

CFLAGS =  -Wall -g -std=c++11

all: Grade_Calculator

Grade_Calculator: application.o department.o  
	g++ -o Grade_Calculator application.o department.o ${CFLAGS}

application.o: application.cpp application.h department.h header.h
	g++ -c application.cpp ${CFLAGS}

department.o: department.cpp department.h header.h
	g++ -c department.cpp ${CFLAGS}

