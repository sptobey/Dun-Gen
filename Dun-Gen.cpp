/* Dun-Gen.cpp
 * Christopher Audette,
 * Samuel P. Tobey,
 * David Bittle,
 * Philip Rowe
 */
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
#include "Subdungeon.h"

#define BLANK 0
#define FLOOR 1
#define WALL 2

using namespace std;

class Dungeon;


/* Dungeon class */
class Dungeon {
private:
  short unsigned int** dCont = NULL;
  void buildEmpty();
  void buildDungeon(unsigned short rax, unsigned short rin, unsigned short rum);
public:
  Dungeon(int w, int h, unsigned long int s);
  Dungeon(int w, int h);
  Dungeon();
  unsigned long int seed;
  int height, width;
  void outputDungeon(std::string name);
};
// Full Constructor
Dungeon::Dungeon (int w, int h, unsigned long int s) {
  seed = s;
  width = ((w <= 30) ? 30 : w);
  height = ((h <= 30) ? 30 : h);
  buildEmpty();
  int w_trunc = width/3;      // The maximum number of rooms is the product of two floor divisions,
  int h_trunc = height/3;     // since the minimum room is 3 by 3.
  buildDungeon(9, ((width*height)/4), (w_trunc*h_trunc));
}

// Constructor w/out Seed
Dungeon::Dungeon(int w, int h) {
  srand(time(NULL));
  seed = rand();
  width = ((w <= 30) ? 30 : w);
  height = ((h <= 30) ? 30 : h);
  buildEmpty();
  int w_trunc = width/3;      // The maximum number of rooms is the product of two floor divisions,
  int h_trunc = height/3;     // since the minimum room is 3 by 3.
  buildDungeon(9, ((width*height)/4), (w_trunc*h_trunc));
}

// Default Constructor
Dungeon::Dungeon(){
  srand(time(NULL));
  seed = rand();
  width = 30;
  height = 30;
  buildEmpty();
  buildDungeon(9, 225, 100);
}

void Dungeon::outputDungeon(string dungeon_name){
  dungeon_name.append(".txt");
  const char* c = dungeon_name.c_str();
  std::ofstream ofs(c);
  if(!ofs) {
    std::cerr<<"Failed to open output file"<<std::endl;
  }
  
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      if(dCont[i][j] == BLANK) {
        ofs << ' ';
      } else if(dCont[i][j] == FLOOR) {
        ofs << '.';
      } else if(dCont[i][j] == WALL) {
        ofs << '#';
      } else {
        ofs<<dCont[i][j];
      }
    }
    ofs<<"\n";
  }
  ofs.close();
}

// Builds a dungeon full of blank tiles
void Dungeon::buildEmpty(){
  dCont = new short unsigned int*[height];  //hooray! Pointers.  Note that this isn't actually deleted anywhere yet.
  for(int k = 0; k < height; ++k){
    dCont[k] = new short unsigned int[width];
  }
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      dCont[i][j] = BLANK;
    }
  }
}

// Builds the actual full dungeon from one full of blank tiles.
void Dungeon::buildDungeon(unsigned short rmin, unsigned short rmax, unsigned short rnum){
  // Using the given seed guarantees it will generate the same dungeon every for the same seed
  srand(Dungeon::seed);
  unsigned short roomMax, roomMin, roomNumMax;
  Subdungeon **rooms;
  roomMax = rmax;         // Maximum room area
  roomMin = rmin;         // Minimum room area
  roomNumMax = rnum;      // Maximum number of rooms possible
  rooms = new Subdungeon *[roomNumMax];
  
  // Generating list of rooms
  for(int r = 0; r < roomNumMax; r++){
    int posx = (rand() % (Dungeon::width - 4))+1;   // corner (horizontal) can be anywhere except edges and 2 units from the right
    int posy = (rand() % (Dungeon::height - 4))+1;  // corner (vertical) an be anywhere except edges and 2 units from the bottom
    int roomWidth = 0;
    int roomHeight = 0;
    // Change dimentions of the room until we have a room area between our max and our min.
    while ((roomWidth*roomHeight < roomMin) || (roomWidth*roomHeight > roomMax)){ 
      if(posx >= (Dungeon::width/2)) {
        int r = rand()%((Dungeon::width/2) - 3 + (width%2))+3;
        roomWidth = r - ((posx+r) - (width-1));
      } else {
        roomWidth = rand()%((Dungeon::width/2) - 3 + (width%2))+3;
      }
      if(posy >= (Dungeon::height/2)) {
        int r = rand()%((Dungeon::height/2) - 3 + (height%2))+3;
        roomHeight = r - ((posy+r) - (height-1));
      } else {
        roomHeight = rand()%((Dungeon::height/2) - 3 + (height%2))+3;
      }
    }
    rooms[r] = new Subdungeon(0, posx, posy, roomWidth, roomHeight);
  }
  
  // Placing rooms; will just re-key and place a different room if a room fails a test.
  // k is room number
  for (int k = 0; k < roomNumMax; ++k){
	  // Flag for room overlap
	  bool roomOverlap = false;
	  // boundsx[0] in Subdungeon::shapeSize is posx
	  int posx = rooms[k]->boundsx[0]; 
	  // boundsx[1] in Subdungeon::shapeSize is posx + roomWidth-1
	  int posxEnd = rooms[k]->boundsx[1];
	  // boundsy[0] in Subdungeon::shapeSize is posy
	  int posy = rooms[k]->boundsy[0]; 
	  // boundsy[1] in Subdungeon::shapeSize is posy + roomHeight-1
	  int posyEnd = rooms[k]->boundsy[1];
	  
	  // Before placing room, check if room will overlap with any other room in Dungeon	 
	   
	  // Dungeon::buildEmpty convention that i associated with height, j with width
	  // Check every x,y position in potential room location by nested loops
	  for (int j = posx; j < posxEnd; ++j){
		  for (int i = posy; i < posyEnd; ++i){
			  // Check if each space is blank, if not, then room overlap
			  if (dCont[i][j] != BLANK){
				  roomOverlap = true;
				  //set i, j to break out of loop
				  j = posxEnd;
				  i = posyEnd;
			  }
		  }
	  }
	  // Place room if no overlap
	  if (!roomOverlap){
		  // Do nested loops again to label each space FLOOR
		  for (int j = posx; j < posxEnd; ++j){
			  for (int i = posy; i < posyEnd; ++i){
				  dCont[i][j] = FLOOR;
				  // Place wall on outer edges of room
				  // Left and right end column walls first
				  dCont[i][0] = WALL;
				  dCont[i][posyEnd] = WALL;
				  // Bottom and top row walls next
				  dCont[0][j] = WALL;
				  dCont[posxEnd][j] = WALL;
			  }
		  }
	  }
  } 

// Place walls on the edges of the dungeon
  for(int i = 0; i < height; i++){
    dCont[i][0] = WALL;
    dCont[i][width-1]= WALL;
  }
   for(int j = 0; j < width; j++){
    dCont[0][j] = WALL;
    dCont[height-1][j] = WALL;
  }
  
  
  
  

  /* Pathfinding algorithm here maybe?  Set it up how you want.
  // Maybe should take args for options?  Still thinking this one out.*/
}

/* End Dungeon class */


int main() {
  
  unsigned long int s;
  int w,h;
  string n;
  std::cout<<"Please enter a width, a height, a seed, and a name:"<<std::endl;
  std::cin>> w >> h >> s >> n;
  Dungeon my_dungeon = Dungeon(w,h,s);
  my_dungeon.outputDungeon(n);
  
  return 0;
}
