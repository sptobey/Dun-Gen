# Makefile for Dun-Gen

all: output
	@echo cleaning...
	@make clean
	@echo Success!

output: output.o
	g++ output.cpp -o output -L output.o
output.o: 
	g++ -c -Wall output.cpp -o output.o
clean:
	@rm -f *.o
