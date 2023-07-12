#include "Basic.h"
#include "Game.h"

Basic::Basic() : Bloon(1, 0) {
  //default constructor
}


Basic::Basic(int health, int location) : Bloon(health, location) {
  //overloaded
}


Basic::~Basic() {}//destructor


int Basic::Pop(int damage) {//Description: Changes the color of the bloon based on how many health it has left
  string bloonColor = GetColor();
  if (bloonColor != "gone"){
      cout << "The " << GetColor() << " bloon pops!" << endl;//red bloon pops
  }
  int num_pops = min(damage, GetHealth());
  SetHealth(GetHealth() - num_pops);
  return num_pops;

}


string Basic::GetColor() {// Description: Returns the current color of a bloon //TODO: make it work with enums cuz idk how to do that
  if (GetHealth() >= 6) {
    m_color = "black";
  } else {
    switch (GetHealth()) {
      case 1:
        m_color = "red";
        break;
      case 2:
        m_color = "blue";
        break;
      case 3:
        m_color = "green";
        break;
      case 4:
        m_color = "yellow";
        break;
      case 5:
        m_color = "pink";
        break;
      default: 
        m_color = "gone";
        break;
    }
  }
  return m_color;
}
