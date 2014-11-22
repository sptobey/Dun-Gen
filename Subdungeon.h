#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

/*! Begin Subdungeon class */
//! This is a designator laid out on rooms, complete with number, position, etc.

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
    short unsigned int* boundsTop;
    short unsigned int* boundsBot;
    short unsigned int height;
    short unsigned int width;
};

unsigned short int Subdungeon::total = 0;

/*! 
 * @brief Subdungeon constructor
 * 
 * @param posx x coordinate for corner closest to 0 for rectangle
 * @param posy y coordinate for corner closest to 0 for rectangle
 * @param h height for subdungeon
 * @param w width for subdungeon
 * @param shape room shape designator (rectangles, right triangles, 
 * equalaterial triangles, etc)
 * 
 * will be different for other room shapes, particularly hexagons 
 * desc is room description, which should be created by a function.
 */
Subdungeon::Subdungeon(int shape, int posx, int posy, int h, int w){
  total++;
  key = total;
  height = h;
  width = w;
  shapeSize(shape, posx, posy, h, w);
  randDescribe();
}
/*! 
 * @brief Subdungeon shape size constructor
 * 
 * @param posx x coordinate for corner closest to 0 for rectangle
 * @param posy y coordinate for corner closest to 0 for rectangle
 * @param h height for subdungeon
 * @param w width for subdungeon
 * @param s room shape designator (rectangles, right triangles, 
 * equalaterial triangles, etc)
 * 
 * will be different for other room shapes, particularly hexagons 
 * desc is room description, which should be created by a function.
 */
void Subdungeon::shapeSize(int s, int posx, int posy, int h, int w){
  if(s == 0){ //! Rectangular room; we may not have time to implement more
    boundsTop = new short unsigned int [2];
    boundsBot = new short unsigned int [2];
    boundsTop[0] = posx;
    boundsTop[1] = posx+w-1;
    boundsBot[0] = posy;
    boundsBot[1] = posy+h-1;
  }
  else{
    cout << "Invalid shape.";
  }
}
/*! 
 * @brief Subdungeon output description
 * 
 * @param x width in feet
 * @param y height in feet
 */
void Subdungeon::randDescribe(){  //! More might be added to this later
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



/*! End Subdungeon class */
