#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

/* Begin Subdungeon class */
// This is a designator laid out on rooms, complete with number, position, etc.

using namespace std;

class Subdungeon {
  private:
    void shapeSize(int s, int posx, int posy, int h, int w);
	void randDescribe();
  public:
    Subdungeon(int shape, int posx, int posy, int h, int w);
    unsigned short int key;  //What number each room corresponds to.
	static unsigned short int total;
	std::string desc;
	short unsigned int* boundsx;
	short unsigned int* boundsy;
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
