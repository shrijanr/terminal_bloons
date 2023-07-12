#include "Dart.h"


Dart::Dart() : Monkey("Dart", 1, 0) {}//default


Dart::Dart(string type, int damage, int location) : Monkey(type, damage, location) {}//overloaded


Dart::~Dart() {}//destructor


int Dart::Attack(vector<Bloon*> bloons) {//attack function, pops first in vector
    int totalPops = 0;
    bool attacked = false; 

    for (Bloon* bloon : bloons) {
        //string bloonColor = bloons[i]->GetColor();
        // check if same loc, health > o, and if attacked already
        if (bloon->GetLocation() == GetLocation() && bloon->GetHealth() > 0 && !attacked) {
            int damage = GetDamage();
            totalPops += bloon->Pop(damage);
            attacked = true;
        }
    }
    
    return totalPops;
}