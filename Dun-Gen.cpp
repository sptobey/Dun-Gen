// Test for outputting text into a new file
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define FLOOR 0
#define WALL 1

/* Dungeon class */
class Dungeon {
private:
public:
  int seed;
  int height, width;
  Dungeon(int, int, int);
};
// Constructor
Dungeon::Dungeon(int s, int w, int h) {
  seed = s;
  width = w;
  height = h;
}
/* End Dungeon class */

int main() {
  
  std::ofstream ofs("test.txt");
  
  if(!ofs) {
    std::cerr<<"Failed to open output file"<<std::endl;
  }
  
  ofs<<"\nThis is a test.\nRandom text here...\n\n";
  ofs.close();
  
  return 0;
}
