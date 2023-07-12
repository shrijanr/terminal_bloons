#include "Monkey.h"

Monkey::Monkey() {//default
  m_damage = 0;
  m_type = "";
  m_location = 0;
}

Monkey::Monkey(string type, int damage, int location) {//overloaded
  m_type = type;
  m_damage = damage;
  m_location = location;
}

Monkey::~Monkey() {} //destructor

int Monkey::GetDamage() {//return damage
  return m_damage;
}

string Monkey::GetType() {//return m_type
  return m_type;
}

int Monkey::GetLocation() {//return location
  return m_location;
}

void Monkey::SetDamage(int damage) {//set damage
  m_damage = damage;
}

void Monkey::SetType(string type) {//set type
  m_type = type;
}

void Monkey::SetLocation(int location) {//set location
  m_location = location;
}

ostream& operator<<(ostream& outos, Monkey& m) {
  outos << m.m_type << " Monkey: Location " << m.m_location << "Damage: " << m.m_damage << endl;
  return outos;
}
