// Test for outputting text into a new file
#include <fstream>
#include <iostream>

// g++ -c -Wall output.cpp -o output.o
// g++ output.cpp -o output -L output.o
// ./output
// cat test.txt
// :)

int main() {
	
	std::ofstream ofs("test.txt");
	
	if(!ofs) {
		std::cerr<<"Failed to open output file"<<std::endl;
	}
	
	ofs<<"\nThis is a test.\nRandom text here...\n\n";
	ofs.close();
	
	return 0;
}
