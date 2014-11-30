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
	string roomtype();
  public:
    Subdungeon(int shape, int posx, int posy, int h, int w, long unsigned int s);
    ~Subdungeon();
    unsigned short int key;  //What number each room corresponds to.
	void rekey(unsigned short int k);
    static unsigned short int total;
    std::string desc;
    short unsigned int* boundsTop;
    short unsigned int* boundsBot;
    short unsigned int height;
    short unsigned int width;
	long unsigned int seed;
	string description();
};

unsigned short int Subdungeon::total = 0;

Subdungeon::~Subdungeon() {
  //delete boundsTop;
  //delete boundsBot;
}

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
Subdungeon::Subdungeon(int shape, int posx, int posy, int h, int w, long unsigned int s){
  total++;
  key = total;
  height = h;
  width = w;
  seed = s;
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

void Subdungeon::rekey(unsigned short int k){
  Subdungeon::key = k;
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
  x << (Subdungeon::width-2) * 5;
  y << (Subdungeon::height-2) * 5;
  std::string xs, ys;
  xs = x.str();
  ys = y.str();
  std::string hold;
  hold = "This room is ";
  hold.append(xs);
  hold.append(" feet by ");
  hold.append(ys);
  hold.append(" feet.  ");
  hold.append(roomtype());
  desc = hold;
}

/*!
 * @brief The bulk of the Subdungeon description, including descriptors
 * 
 * @param type What kind of room the room is.
 * @param hold The string returned.
 * */
string Subdungeon::roomtype(){
  short int roll = (rand() % 20);
  char type;
  string hold;
  if (roll <= 11){  //! Determines the type of room.
    type = 'e'; // Empty room
  }
  else if (roll > 11 && roll <= 13){
    type = 'm'; // Monster Only
  }
  else if (roll > 13 && roll <= 16){
    type = 'f'; // Monster and Treasure
  }
  else if (roll == 17){
    type = 's'; // Special
  }
  else if (roll == 18){
    type = 'r'; // Trick/Trap
  }
  else if (roll == 19){
    type = 't'; // Treasure
  }
  else {
    cout << "Somehow the roll failed. \n";
	return "";
  }
  
  if(type != 's' && type != 'r'){ //! Borrowed liberally from Courtney Campbell's "Tricks" Document, available at http://hackslashmaster.blogspot.com/2011/02/on-tricks-empty-rooms-and-basic-trap.html
    roll = (rand() % 92);
	if (roll == 0){
	  hold = "This room is an amphitheatre.  ";
	}
	else if (roll == 1){
	  hold = "This room is an antechamber.  ";
	}
	else if (roll == 2){
	  hold = "This room is an arena.  ";
	}
	else if (roll == 3){
	  hold = "This room is an arsenal.  ";
	}
	else if (roll == 4){
	  hold = "This room is an assemblage.  ";
	}
	else if (roll == 5){
	  hold = "This room is an audience hall.  ";
	}
	else if (roll == 6){
	  hold = "This room is an aviary.  ";
	}
	else if (roll == 7){
	  hold = "This room is a banquet hall.  ";
	}
	else if (roll == 8){
	  hold = "This room is a barracks.  ";
	}
	else if (roll == 9){
	  hold = "This is a bathroom.  ";
	}
	else if (roll == 10){
	  hold = "This is a bedroom.  ";
	}
	else if (roll == 11){
	  hold = "This room is a bestiary.  ";
	}
	else if (roll == 12){
	  hold = "This room is a cell.  ";
	}
	else if (roll == 13){
	  hold = "This room is a chantry.  ";
	}
	else if (roll == 14){
	  hold = "This room is a chapel.  ";
	}
	else if (roll == 15){
	  hold = "This is a cistern room.  ";
	}
	else if (roll == 16){
	  hold = "This is a classroom.  ";
	}
	else if (roll == 17){
	  hold = "This is a closet.  ";
	}
	else if (roll == 18){
	  hold = "This room is a combat pit.  ";
	}
	else if (roll == 19){
	  hold = "This room is a confessional.  ";
	}
	else if (roll == 20){
	  hold = "This is a conjuring room.  ";
	}
	else if (roll == 21){
	  hold = "This is a courtroom.  ";
	}
	else if (roll == 22){
	  hold = "This room is a crematorium.  ";
	}
	else if (roll == 23){
	  hold = "This room is a crypt.  ";
	}
	else if (roll == 24){
	  hold = "This room is a den.  ";
	}
	else if (roll == 25){
	  hold = "This is a dining room.  ";
	}
	else if (roll == 26){
	  hold = "This is a divination chamber.  ";
	}
	else if (roll == 27){
	  hold = "This is a dressing room.  ";
	}
	else if (roll == 28){
	  hold = "This is an embalming chamber.  ";
	}
	else if (roll == 29){
	  hold = "This room is a forge.  ";
	}
	else if (roll == 30){
	  hold = "This room is a foyer.  ";
	}
	else if (roll == 31){
	  hold = "This is a gallery.  ";
	}
	else if (roll == 32){
	  hold = "This is a game room.  ";
	}
	else if (roll == 33){
	  hold = "This is a great hall.  ";
	}
	else if (roll == 34){
	  hold = "This is a guard room.  ";
	}
	else if (roll == 35){
	  hold = "This room is a gymnasium.  ";
	}
	else if (roll == 36){
	  hold = "This is a less than great hall.  ";
	}
	else if (roll == 37){
	  hold = "This room is a harem.  ";
	}
	else if (roll == 38){
	  hold = "This is a room with a lot of writing on the walls.  ";
	}
	else if (roll == 39){
	  hold = "This is an interrogation room.  ";
	}
	else if (roll == 40){
	  hold = "This room is a kennel.  ";
	}
	else if (roll == 41){
	  hold = "This room is a kitchen.  ";
	}
	else if (roll == 42){
	  hold = "This room is a laboratory.  ";
	}
	else if (roll == 43){
	  hold = "This is a lair of some creature.  ";
	}
	else if (roll == 44){
	  hold = "This room is a larder.  ";
	}
	else if (roll == 45){
	  hold = "This room is a library.  ";
	}
	else if (roll == 46){
	  hold = "This room is a lounge.  ";
	}
	else if (roll == 47){
	  hold = "This is a map room.  ";
	}
	else if (roll == 48){
	  hold = "This room is a mass grave.  ";
	}
	else if (roll == 49){
	  hold = "This is a meditation chamber.  ";
	}
	else if (roll == 50){
	  hold = "This is a meeting chamber.  ";
	}
	else if (roll == 51){
	  hold = "This is a mess hall.  ";
	}
	else if (roll == 52){
	  hold = "This is a ascetic's cell.  ";
	}
	else if (roll == 53){
	  hold = "This room is a morgue.  ";
	}
	else if (roll == 54){
	  hold = "This room is a museum.  ";
	}
	else if (roll == 55){
	  hold = "This is a music room.  ";
	}
	else if (roll == 56){
	  hold = "This room is an observatory.  ";
	}
	else if (roll == 57){
	  hold = "This room is an office.  ";
	}
	else if (roll == 58){
	  hold = "This is a padded room.  ";
	}
	else if (roll == 59){
	  hold = "This is a planning room.  ";
	}
	else if (roll == 60){
	  hold = "This room has a pool.  ";
	}
	else if (roll == 61){
	  hold = "This room is a prison.  ";
	}
	else if (roll == 62){
	  hold = "This room is a privy.  ";
	}
	else if (roll == 63){
	  hold = "This is a reception chamber.  ";
	}
	else if (roll == 64){
	  hold = "This is a robing room.  ";
	}
	else if (roll == 65){
	  hold = "This room is a salon.  ";
	}
	else if (roll == 66){
	  hold = "This room is a scriptorium.  ";
	}
	else if (roll == 67){
	  hold = "This is a servants dorm.  ";
	}
	else if (roll == 68){
	  hold = "This room is a shrine.  ";
	}
	else if (roll == 69){
	  hold = "This room is a smokehouse.  ";
	}
	else if (roll == 70){
	  hold = "This room is statuary.  ";
	}
	else if (roll == 71){
	  hold = "This room is a stockade.  ";
	}
	else if (roll == 72){
	  hold = "This room is used for storage.  ";
	}
	else if (roll == 73){
	  hold = "This room is a study.  ";
	}
	else if (roll == 74){
	  hold = "This is a summoning room.  ";
	}
	else if (roll == 75){
	  hold = "This room is a tannery.  ";
	}
	else if (roll == 76){
	  hold = "This room is a temple.  ";
	}
	else if (roll == 77){
	  hold = "This is a throne room.  ";
	}
	else if (roll == 78){
	  hold = "This room is a tomb.  ";
	}
	else if (roll == 79){
	  hold = "This is a torture chamber.  ";
	}
	else if (roll == 80){
	  hold = "This is a training room.  ";
	}
	else if (roll == 81){
	  hold = "This is a treasury.  ";
	}
	else if (roll == 82){
	  hold = "This is a trophy room.  ";
	}
	else if (roll == 83){
	  hold = "This is a waiting room.  ";
	}
	else if (roll == 84){
	  hold = "This room is a wardrobe.  ";
	}
	else if (roll == 85){
	  hold = "This is a well room.  ";
	}
	else if (roll == 86){
	  hold = "This room is a workshop.  ";
	}
	else if (roll == 87){
	  hold = "This room is a vault.  ";
	}
	else if (roll == 88){
	  hold = "This room is a vestiary.  ";
	}
	else if (roll == 89){
	  hold = "This room is a vestibule.  ";
	}
	else if (roll == 90){
	  hold = "This room is a zoo.  ";
	}
	else if (roll == 91){
	  hold = "This room is a bar.  ";
	}
	else{
	  cout << "Somehow the roll failed.  ";
	  return "";
	}
  }
  
  return hold;
  
}

string Subdungeon::description(){
  string hold, zs;
  stringstream z;
  z << Subdungeon::key;
  zs = z.str();
  hold = "Room ";
  hold.append(zs);
  hold.append("\n");
  hold.append(Subdungeon::desc);
  hold.append("\n");
  return hold;
}



/*! End Subdungeon class */
