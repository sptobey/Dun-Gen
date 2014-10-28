# Makefile for Dun-Gen

all: output
	@make clean

output: Dun-Gen.o
	g++ Dun-Gen.cpp -o Dun-Gen -L Dun-Gen.o
output.o: 
	g++ -c -Wall Dun-Gen.cpp -o Dun-Gen.o
clean:
	@rm -f *.o
