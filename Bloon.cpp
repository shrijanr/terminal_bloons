#include "Bloon.h"


Bloon::Bloon() { //default
  m_health = 0;
  m_location = 0;
}


Bloon::Bloon(int health, int location) {//overloaded
  m_health = health;
  m_location = location;
}


Bloon::~Bloon() {}//destructor


int Bloon::GetHealth() { //health getter
  return m_health;
}


void Bloon::SetHealth(int health) {//health setter
  m_health = health;
}


int Bloon::GetLocation() {//return location
  return m_location;
}


void Bloon::SetLocation(int location) {//set location
  m_location = location;
}


ostream& operator<<(ostream& output, Bloon& b) { 
  output << "<<Bloons>>\n";
  for (int i = 1; i <= 3; i++) {
    output << "**Location " << i << "**\n";
    output << "--Monkeys--\n";
    output << "None\n";
    output << b << endl;
    output << endl;
  }
  return output;
}
