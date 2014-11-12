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
  width = ((w <= 0) ? 1 : w);
  height = ((h <= 0) ? 1 : h);
  buildEmpty();
  buildDungeon(3, ((w*h)/4), ((w*h)/3));
}

// Constructor w/out Seed
Dungeon::Dungeon(int w, int h) {
  srand(time(NULL));
  seed = rand();
  width = ((w <= 0) ? 1 : w);
  height = ((h <= 0) ? 1 : h);
  buildEmpty();
  buildDungeon(3, ((w*h)/4), ((w*h)/3));
}

// Default Constructor
Dungeon::Dungeon(){
  srand(time(NULL));
  seed = rand();
  width = 30;
  height = 30;
  buildEmpty();
  buildDungeon(3, 8, 20);
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
void Dungeon::buildDungeon(unsigned short rax, unsigned short rin, unsigned short rum){
//Using the seed finally; this guarantees any given seed will generate the same dungeon every time
    srand(Dungeon::seed);
	unsigned short roomMax, roomMin, roomNumMax;
	Subdungeon **rooms;
	roomMax = rax; // Maximum room area
	roomMin = rin; // Minimum room area
	roomNumMax = rum; // Maximum number of rooms that can be placed
	rooms = new Subdungeon *[roomNumMax];
	
	// Generating list of rooms
	for(int r = 0; r < roomNumMax; r++){
	  int posx = (rand() % (Dungeon::width - 1))+1; //corner can be anywhere except edges
	  int posy = (rand() % (Dungeon::height - 1))+1; //same as above
	  int roomWidth = 0;
	  int roomHeight = 0;
	  // This loop continues going until we have a room area between our max and our min.
	  while ((roomWidth*roomHeight <= roomMin)  || (roomWidth*roomHeight >= roomMax)){ 
	    roomWidth = (rand()%(roomMax/2))+1;
		roomHeight = (rand()%(roomMax/2))+1;
		// checks if the room goes out of bounds of the dungeon; if so, resizes the room again.
		if ( (posx+roomWidth-1 >= Dungeon::width) || (posy+roomHeight-1 >= Dungeon::height)){
		  roomWidth = 0;
		}
		
	  }
	  rooms[r] = new Subdungeon(0, posx, posy, roomWidth, roomHeight);
	}
	
	// Placing rooms; will just rekey and place a different room if a room fails a test.
	// Haven't written yet
	for (int k = 0; k <= roomNumMax; k++){
	}

//a couple loops to put walls on the edges of the dungeon
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
