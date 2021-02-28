all: main

main: coopThread.cpp switch.s
	g++ -g -o switch.o -c switch.s
	g++ -g -o coopThread.o -c coopThread.cpp
	g++  -o coopThread coopThread.o switch.o
