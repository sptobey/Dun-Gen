/* Dun-Gen.cpp
 * Christopher Audette,
 * Samuel P. Tobey,
 * David Bittle,
 * Philip Rowe
 */
#include <fstream>
#include <istream>
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
  short unsigned int** dCont;
  void buildEmpty();
  void buildDungeon(unsigned short rax, unsigned short rin, unsigned short rum);
public:
  Dungeon(int w, int h, unsigned long int s);
  Dungeon(int w, int h);
  Dungeon();
  unsigned long int seed;
  int height, width;
  void outputDungeon(std::string name);
  void printDungeon(string fileName);
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

void Dungeon::printDungeon(string fileName){
  ifstream dungeonOutput;
  fileName.append(".txt"); 
  dungeonOutput.open(fileName.c_str());
  cout << dungeonOutput.rdbuf();
  dungeonOutput.close();
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
    rooms[r] = new Subdungeon(0, posx, posy, roomHeight, roomWidth);
  }
  
  // Placing rooms; will just re-key and place a different room if a room fails a test.
  for (int k = 0; k < roomNumMax; ++k){
    bool roomOverlap = false;
    int posx = rooms[k]->boundsTop[0]; 
    int posxEnd = rooms[k]->boundsTop[1];
    int posy = rooms[k]->boundsBot[0]; 
    int posyEnd = rooms[k]->boundsBot[1];
    
    // Before placing room, check if room will overlap with any other room in Dungeon   
     
    // Dungeon::buildEmpty convention that i associated with height, j with width
    // Check every x,y position in potential room location by nested loops
    for (int i = posy; i <= posyEnd; ++i){
      for (int j = posx; j <= posxEnd; ++j){
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
      // Floor
      for (int i = (posy+1); i <= (posyEnd-1); ++i){
        for (int j = (posx+1); j <= (posxEnd-1); ++j){
          dCont[i][j] = FLOOR;
        }
      }
      // Left and Right Walls
      for (int i = posy; i <= posyEnd; ++i) {
        dCont[i][posx   ] = WALL;
        dCont[i][posxEnd] = WALL;
      }
      // Bottom and Top Walls
      for (int j = posx; j <= posxEnd; ++j) {
        dCont[posy   ][j] = WALL;
        dCont[posyEnd][j] = WALL;
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

/*!
 * @mainpage Project Dun-Gen
 * homepage in Doxygen documentation
 * 
 * @brief Takes user inputs for width, height, seed, and name
 * and creates a dungeon. Also takes user input for printing dungeon.
 * @param w width for dungeon
 * @param h height for dungeon
 * @param s seed for dungeon
 * @param n name for dungeon
 * @param yes to print dungeon
 * @param no not print dungeon
 */

int main() {
  
  unsigned long int s;
  int w,h;
  string n;
  string yes_no;
  std::cout<<"Please enter a width, a height, a seed, and a name:"<<std::endl;
  std::cin>> w >> h >> s >> n;
  Dungeon my_dungeon = Dungeon(w,h,s);
  my_dungeon.outputDungeon(n);
  
  cout<<"Would you like to see the dungeon now? (yes or no)"<<endl;
  cin>> yes_no;
  if(yes_no == "yes" or yes_no == "Yes")
  {
    my_dungeon.printDungeon(n);
  }
    
  return 0;
}
