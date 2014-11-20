/*! Dun-Gen.cpp
 * @author Christopher Audette,
 * @author Samuel P. Tobey,
 * @author David Bittle,
 * @author Philip Rowe
 * @brief A project that builds a 'dungeon' that has well and rooms and paths generated between them. The number of rooms is random and the size can be passed in
 */
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
#include "Subdungeon.h"
#include <istream>
#include <list>
#include <typeinfo>


#define BLANK 0
#define FLOOR 1
#define WALL 2
#define PATH 8
#define DOOR 6

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
  list<Subdungeon> roomList;
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

/*!
 * 
 * @brief puts the dungeon into a file
 * @param dungeon_name the name of the dungeon that was passed in. It is made as a .txt file
 * */

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



/*!
 * @brief prints the dungeon file
 * @param dungeon_name the name of the dungeon that was passed in. It is made as a .txt file
 * */
 
void Dungeon::printDungeon(string fileName){
  ifstream dungeonOutput;
  fileName.append(".txt"); 
  dungeonOutput.open(fileName.c_str());
  cout << dungeonOutput.rdbuf();
  }
  


  
/*!
 * @brief builds the main dungeon
 * @param rmin minimum room area
 * @param rmax max room area
 * @param rnum max number of rooms
 * */
 

// Builds the actual full dungeon from one full of blank tiles.
void Dungeon::buildDungeon(unsigned short rmin, unsigned short rmax, unsigned short rnum){
  // Using the given seed guarantees it will generate the same dungeon every for the same seed
  srand(Dungeon::seed);
  unsigned short roomMax, roomMin, roomNumMax;
  Subdungeon **rooms;
  roomMax = rmax;        
  roomMin = rmin;         
  roomNumMax = rnum;      
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
        
        //Added checks so that there are spaces between rooms
        if (dCont[i][j] != BLANK or dCont[i+1][j] or dCont[i-1][j] != BLANK or dCont[i][j+1] != BLANK or dCont[i][j-1] != BLANK){
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
   
   //adds room to a list of rooms
     roomList.push_back(* rooms[k]);
   
   //   cout << "a room has been made with a central point of " << posxEnd-posx << "," << posyEnd-posy << endl;
    
    }
    
    
    
  }
  
 
		Subdungeon oldDungeon = *roomList.begin(); 
//  Subdungeon startRoom;
//makes a "door" on the left hand side starts to find a way around
  for (list<Subdungeon>::iterator iterator = roomList.begin(), end = roomList.end(); iterator != end; ++iterator) {
  //  if(startRoom != NULL)
		int doory = iterator->boundsBot[0]+(iterator->boundsBot[1]-iterator->boundsBot[0])/2;
		//int midx = iterator->
		int doorx = iterator->boundsTop[0];
		dCont[doory][doorx]= DOOR;
		dCont[doory][doorx-1]= PATH;
		doorx = doorx-1;
		//if(oldDungeon
		
		if (iterator != roomList.begin()){
			
			//Subdungeon oldDungeon = roomList.back();
			cout << oldDungeon.boundsBot[0]  <<endl;
			
			int destinationDoory = oldDungeon.boundsBot[0]+(oldDungeon.boundsBot[1]-oldDungeon.boundsBot[0])/2;
			int destinationDoorx = oldDungeon.boundsTop[0];
		//	cout << "the destination is: "<< destinationDoory << destinationDoorx << endl;
			
			
	//		cout << "the doors location is " << doorx << endl;
	//		cout << "the destinations is " << destinationDoorx << endl;	
			

			//basic path finding stuff		
			//while(doory!=destinationDoory && doorx != destinationDoorx-1){
				
			int i = 0;
			while((doory!=destinationDoory || doorx != destinationDoorx) && i<100){
				
				if(doory > destinationDoory && dCont[doory-1][doorx]!=WALL && dCont[doory-1][doorx]!=DOOR){
						dCont[doory-1][doorx]= PATH;
						doory = doory -1;
	
					}
				
				if(doory < destinationDoory && dCont[doory+1][doorx]!=WALL && dCont[doory+1][doorx]!=DOOR){
						dCont[doory+1][doorx]= PATH;
						doory = doory +1;
					}
			
			// && dCont[doory][doorx-1]!=WALL
				if(doorx < destinationDoorx  && dCont[doory][doorx+1]!=WALL && dCont[doory][doorx+1]!=DOOR){
							dCont[doory][doorx+1]= PATH;
							doorx = doorx +1;
					}
				if(doorx > destinationDoorx && dCont[doory][doorx-1]!=WALL  && dCont[doory][doorx-1]!=DOOR){
	
						dCont[doory][doorx-1]= PATH;
						doorx = doorx -1;
					}
			i++;
			//if(i%10==0){cout<<destinationDoorx << destinationDoory<< endl;}
			
			oldDungeon = *iterator;
			}
			
			
			//while(doory > destinationDoory && dCont[doory][doorx-1]!=WALL){
						//dCont[doory][doorx-1]= PATH;
						//doory = doory -1;
	
					//}
					//doory++;
				//// && dCont[doory][doorx-1]!=WALL
				//while(doorx-1 < destinationDoorx-1  && dCont[doory][doorx-1]!=WALL){
	
						//dCont[doory][doorx-1]= PATH;
						//doorx = doorx +1;
					//}
				//while(doorx-1 > destinationDoorx-1 && dCont[doory][doorx-1]!=WALL){
	
						//dCont[doory][doorx-1]= PATH;
						//doorx = doorx -1;
					//}
				
				//while(doory < destinationDoory && dCont[doory][doorx-1]!=WALL){
						//dCont[doory][doorx-1]= PATH;
						//doory = doory +1;
					//}
			
			
			
			
			}
	//	}
		//cout<<oldDungeon.boundsTop[0]<<endl;
		
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
  string yes_no;
  std::cout<<"Please enter a width, a height, a seed, and a name:"<<std::endl;
  std::cin>> w >> h >> s >> n;
  Dungeon my_dungeon = Dungeon(w,h,s);
  my_dungeon.outputDungeon(n);
  
  cout<<"Would you like to see the dungeon now? (yes or no)"<<endl<<endl;
  cin>> yes_no;
  if(yes_no == "yes" or yes_no == "Yes")
  {
	my_dungeon.printDungeon(n);
  }
    
  return 0;
}
