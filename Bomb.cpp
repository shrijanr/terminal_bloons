#include "Bomb.h"


Bomb::Bomb() : Monkey("Bomb", 1, 0) {}


Bomb::Bomb(string type, int damage, int location) : Monkey(type, damage, location) {}


Bomb::~Bomb() {}


int Bomb::Attack(vector<Bloon*> bloons) {
    int totalPops = 0; //total pops (earns money) for all bloons damaged
//iterate bloons
    for (unsigned int i = 0; i < bloons.size(); i++) { //same logic as boom it just runs once
        string bloonColor = bloons[i]->GetColor();
        if (bloons[i]->GetLocation() == GetLocation()) {
            totalPops += bloons[i]->Pop(GetDamage()); //damage each bloon and get pops for money
        }
    }
    return totalPops; //returns total pops for money
}
