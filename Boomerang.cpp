#include "Boomerang.h"
#include "Game.h"

//default
Boomerang::Boomerang() {
  SetDamage(DAMAGE_BOOM);
  SetType("Boomerang");
  SetLocation(0);
}


Boomerang::Boomerang(string type, int damage, int location) {//overloaded
  SetDamage(damage);
  SetType(type);
  SetLocation(location);
}

//destructor
Boomerang::~Boomerang() {}

int Boomerang::Attack(vector<Bloon*> bloons) { //NOTE: is called twice in game if the type is boomerang
    int totalPops = 0; //total pops (earns money) for all bloons damaged
    //iterate location
    for (unsigned int i = 0; i < bloons.size(); i++) {
        string bloonColor = bloons[i]->GetColor();
        if (bloons[i]->GetLocation() == GetLocation()) {
            totalPops += bloons[i]->Pop(GetDamage()); //damage each bloon and get pops for money
        }
    }
    //initially had boomerang run this for loop twice
    // 
    // for (unsigned int i = 0; i < bloons.size(); i++) {
    //     string bloonColor = bloons[i]->GetColor();
    //     if (bloons[i]->GetLocation() == GetLocation()) {
    //         totalPops += bloons[i]->Pop(GetDamage()); //damage each bloon and get pops for money
    //             if (bloonColor != "gone"){
    //                 cout << "The bloon is now " << bloons[i]->GetColor() << endl;
    //         }
    //     }
    // }
    return totalPops;
}
