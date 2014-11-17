# Makefile for Dun-Gen

all: Dun-Gen
	@make clean

Dun-Gen: Dun-Gen.o
	g++ Dun-Gen.cpp -g -o Dun-Gen -L Dun-Gen.o
Dun-Gen.o: 
	g++ -c -Wall Dun-Gen.cpp -o Dun-Gen.o
clean:
	@rm -f *.o
