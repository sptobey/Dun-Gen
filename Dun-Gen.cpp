// Test for outputting text into a new file
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

#define BLANK 0
#define FLOOR 1
#define WALL 2

using namespace std;

/* Dungeon class */
class Dungeon {
private:
  short unsigned int** dCont = NULL;
  void buildEmpty();
  void buildDungeon();
public:
  Dungeon(int w, int h, unsigned long int s);
  Dungeon(int w, int h);
  Dungeon();
  unsigned long int seed;
  int height, width;
  Dungeon(int, int, int);
};
// Full Constructor
Dungeon::Dungeon (int w, int h, unsigned long int s) {
  seed = s;
  if(width <= 0){
    width = 1;
  }
  else{
    width = w;
  }
  if(height <= 0){
    height = 1;
  }
  else{
    height = h;
  }
  buildEmpty();
  buildDungeon();
}

// Constructor w/out Seed
Dungeon::Dungeon(int w, int h) {
  srand(time(NULL));
  seed = rand();
  if(width <= 0){
    width = 1;
  }
  else{
    width = w;
  }
  if(height <= 0){
    height = 1;
  }
  else{
    height = h;
  }
  buildEmpty();
  buildDungeon();
}

// Default Constructor
Dungeon::Dungeon(){
  srand(time(NULL));
  seed = rand();
  width = 30;
  height = 30;
  buildEmpty();
  buildDungeon();
}

// Builds a dungeon full of blank tiles
void Dungeon::buildEmpty(){
  dCont = new short unsigned int*[width];  //hooray! Pointers.  Note that this isn't actually deleted anywhere yet.
  for(int k = 0; k < height; ++k){
    dCont[k] = new short unsigned int[height];
  }
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
	  dCont[i][j] = BLANK;
	}
  }
}

// Builds the actual full dungeon from one full of blank tiles.
void Dungeon::buildDungeon(){
  /* Pathfinding algorithm here maybe?  Set it up how you want.
  // Maybe should take args for options?  Still thinking this one out.*/
}

/* End Dungeon class */

/* Begin Subdungeon class */
// This is a designator laid out on rooms, complete with number, position, etc.

class Subdungeon {
  private:
    void shapeSize(int s, int posx, int posy, int h, int w);
	void randDescribe();
  public:
    Subdungeon(int shape, int posx, int posy, int h, int w);
    unsigned short int key;  //What number each room corresponds to.
	static unsigned short int total;
	std::string desc;
	short unsigned int* boundsx = NULL;
	short unsigned int* boundsy = NULL;
	short unsigned int height;
	short unsigned int width;
};

unsigned short int Subdungeon::total = 0;

/* Subdungeon constructor, shape is room shape designator (rectangles, right triangles, 
// equalaterial triangles, etc)
// posx and posy are coordinates for corner closest to 0 on both scales for rectangles
// will be different for other room shapes, particularly hexagons 
// desc is room description, which should be created by a function. */
Subdungeon::Subdungeon(int shape, int posx, int posy, int h, int w){
  total++;
  key = total;
  shapeSize(shape, posx, posy, h, w);
  height = h;
  width = w;
  randDescribe();
}

void Subdungeon::shapeSize(int s, int posx, int posy, int h, int w){
  if(s == 0){ //Rectangular room; we may not have time to implement more
    boundsx = new short unsigned int [2];
	boundsy = new short unsigned int [2];
	boundsx[0] = posx;
	boundsx[1] = posx+w-1;
	boundsy[0] = posy;
	boundsy[1] = posy+h-1;
  }
  else{
    cout << "Invalid shape.";
  }
}

void Subdungeon::randDescribe(){  //More might be added to this later
  stringstream x;
  stringstream y;
  x << Subdungeon::width-2;
  y << Subdungeon::height-2;
  std::string xs, ys;
  xs = x.str();
  ys = y.str();
  std::string hold;
  hold = "This room is";
  hold.append(xs);
  hold.append(" feet by ");
  hold.append(ys);
  hold.append(" feet.  ");
  desc = hold;
}



/* End Subdungeon class */



int main() {
  
  std::ofstream ofs("test.txt");
  
  if(!ofs) {
    std::cerr<<"Failed to open output file"<<std::endl;
  }
  
  ofs<<"\nThis is a test.\nRandom text here...\n\n";
  ofs.close();
  
  return 0;
}