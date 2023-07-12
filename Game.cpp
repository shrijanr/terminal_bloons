#include "Game.h"


Game::Game() {//default
    m_curRound = START_ROUND;
    m_curLife = START_LIFE;
    m_curMoney = START_MONEY;
}


Game::~Game() {//destructor
    for (unsigned int i = 0; i < m_bloons.size(); i++) {
        delete m_bloons[i];
        m_bloons[i] = nullptr;
    }

    for (unsigned int i = 0; i < m_monkeys.size(); i++) {
        delete m_monkeys[i];
        m_monkeys[i] = nullptr;
    }
}


void Game::PrintMap() {//print locations of monkeys and bloons
    for (unsigned int i = 1; i <= PATH_LENGTH; i++) {
        cout << "\n**Location " << i << "**\n--Monkeys--\n";
        bool hasMonkey = false;//checker for monkey presence e.g. case None
        for (unsigned int j = 0; j < m_monkeys.size(); j++) {
            if ((unsigned int)m_monkeys[j]->GetLocation() == i) {
                cout << j + 1 << ". " << m_monkeys[j]->GetType() << " Monkey: Location " << i << " Damage: " << m_monkeys[j]->GetDamage() << endl;
                hasMonkey = true;
            }
        }
        if (!hasMonkey) {
            cout << "None\n";
        }

        cout << "<<Bloons>>\n";

        bool hasBloon = false;//checker for bloon presence e.g. case None
        for (unsigned int j = 0; j < m_bloons.size(); j++) {
            unsigned int adjustedLocation = m_bloons[j]->GetLocation() + 1;
            if (adjustedLocation <= PATH_LENGTH && adjustedLocation == i) {
                cout << "Bloon: " << m_bloons[j]->GetColor() << " Health: " << m_bloons[j]->GetHealth() << endl;
                hasBloon = true;
            }
        }
        if (!hasBloon) {
            cout << "None\n";
        }
    }
}




void Game::ImproveMonkey() { //improvemonkey by IMPROVE_VALUE
    int choice;
    bool run = true;

    if (m_monkeys.size() == 0) {//or else user would be stuck in a loop with no way out
        cout << "There are no monkeys to improve" << endl;
        return;
    }

    while (run) {
        cout << "Which monkey would you like to improve (1-" << m_monkeys.size() << ")\n";
        for (unsigned int i = 0; i < m_monkeys.size(); i++) {
            cout << (i + 1) << ". " << m_monkeys[i]->GetType() << " Monkey: Location " << m_monkeys[i]->GetLocation() << " Damage: " << m_monkeys[i]->GetDamage() << endl;
        }
        cin >> choice;

        if (choice < 1 || choice > (int)m_monkeys.size()) {

        } else {
            run = false;
        }
    }

    int cost = COST_IMPROVE;

    if (cost > m_curMoney) {
        cout << "Not enough money to improve monkey. "<< endl;
        return;
    }

    cout << m_monkeys[choice - 1]->GetType() << " Monkey in position " << m_monkeys[choice - 1]->GetLocation() - 1 << " improved!" << endl;
    m_monkeys[choice - 1]->SetDamage(m_monkeys[choice - 1]->GetDamage() + IMPROVE_VALUE);
    m_curMoney -= cost;
}




void Game::BuyMonkey() { //buy a new monkey
  int monkeyType;

  cout << "What type of monkey would you like to buy?" << endl;
  cout << "1. Dart Monkey" << endl;
  cout << "2. Boomerang Monkey" << endl;
  cout << "3. Bomb Monkey" << endl;
  cout << "4. Cancel" << endl;

  cin >> monkeyType;

  if (monkeyType == 4) {
    return;
  }

  int cost;
  string monkeyName;

  switch (monkeyType) {//switch for monkey initializing
    case 1:
      cost = COST_DART;
      monkeyName = "Dart";
      break;
    case 2:
      cost = COST_BOOMERANG;
      monkeyName = "Boomerang";
      break;
    case 3:
      cost = COST_BOMB;
      monkeyName = "Bomb";
      break;
    default:
      cout << "Invalid choice" << endl;
      return;
  }

  if (m_curMoney < cost) { 
    cout << "Not enough money to buy " << monkeyName << " monkey." << endl; //error
    return;
  }
  PlaceMonkey(monkeyType); //call placemonkey
  m_curMoney -= cost;
}



void Game::PlaceMonkey(int choice) { // place new monkey at location, given int choice
    int location;
    cout << "Where would you like to place the new monkey? (1-" << PATH_LENGTH << ")" << endl;
    cin >> location;
    while (location < 1 || location > PATH_LENGTH) {
        cout << "Invalid location. Please choose a location between 1 and " << PATH_LENGTH << endl;
        cin >> location;
    }

    Monkey* newMonkey;//new monkey allocated
    switch (choice) {
        case 1:
            newMonkey = new Dart("Dart", DAMAGE_DART , location);
            break;
        case 2:
            newMonkey = new Boomerang("Boomerang", DAMAGE_BOOM , location);
            break;
        case 3:
            newMonkey = new Bomb("Bomb", DAMAGE_BOMB, location);
            break;
        default:
            PlaceMonkey(choice);//reprompt user if invalid 
            return;
    }

    //populate locations
    newMonkey->SetLocation(location);
    m_monkeys.push_back(newMonkey);
    cout << "New " << newMonkey->GetType() << " Monkey placed in location " << location << endl;
}




void Game::StartGame() { // main loop
    cout << "Welcome to Bloons!" << endl;
    bool run = true;
    while (run) {
        MainMenu();
        cout << "\nThank you for playing Bloons!" << endl;
        run = false;
    }
}



int Game::MainMenu() {
    if (m_curLife <= 0) {
        cout << "Sorry, you have lost the game. "<< endl; //end game if no life
        return 0;
    }
  
        cout << "What would you like to do?" << endl // main menu
            << "1. View Map" << endl
            << "2. Buy New Monkey" << endl
            << "3. Improve Existing Monkey" << endl
            << "4. Progress Round" << endl
            << "5. Check Stats" << endl
            << "6. Quit" << endl;
    
    int choice;
    cin >> choice;
  
    switch (choice) { //main menu switch
        case 1:
            PrintMap();
            break;
        case 2:
            BuyMonkey();
            break;
        case 3:
            ImproveMonkey();
            break;
        case 4:
            PlayRound();
            break;
        case 5:
            Stats();
            break;
        case 6:
            return 0;
        default:
            return MainMenu();
    }
  
    return MainMenu(); //reprompt
}

void Game::Stats() {
    /*  **CURRENT STATS**
    Current Round: 1
    Monkeys Working: 1
    Current Money: 6
    Current Life: 100
    */
   cout << "**CURRENT STATS**" << endl;
  cout << "Current round: " << m_curRound << endl;
  cout << "Monkeys Working: " << m_monkeys.size() << endl;
  cout << "Current Money: " << m_curMoney << endl;
  cout << "Current Life: " << m_curLife << endl;
}

void Game::PlayRound() { //playround
    cout << "Starting round " << m_curRound << endl;
    PopulateBloons();
    MoveBloons();
    ResolveBattle();
    RemovePopped();
    CheckPath();
    cout << "The bloons move along the path" << endl;
    cout << "Round " << m_curRound << " Completed\n";
    m_curRound++;
}




void Game::PopulateBloons() { //populate
    for (int i = 1; i <= m_curRound; i++) {
        int bloonHealth = i;
        Bloon *newBloon = new Basic(bloonHealth, START_BLOON);
        m_bloons.push_back(newBloon);
        cout << "A new " << newBloon->GetColor() << " bloon appears!" << endl;
    }
}



void Game::ResolveBattle() {
    for (Monkey *monkey : m_monkeys) {
        for (Bloon *bloon : m_bloons) {
            //position check
            if (monkey->GetLocation() == bloon->GetLocation()) {
                //keep track of color and bloons at location
                vector<Bloon*> bloonsInLocation = {bloon};
                string bloonColor = bloon->GetColor();
                //ternary operator magic
                cout << "The " << (monkey->GetType() == "Boomerang" ? "Boomerang Monkey throws a Boomerang!" : monkey->GetType() == "Bomb" ? "Bomb shooter launches a bomb!" : monkey->GetType() + " Monkey throws a " + monkey->GetType() + "!") << endl;
                int totalPops = monkey->Attack(bloonsInLocation); //monkey attacks all bloons,
                cout << "The bloon is now " << bloon->GetColor() << endl;// The bloon is now Red
                if (monkey->GetType() == "Boomerang"){
                    totalPops += monkey->Attack(bloonsInLocation);
                    if(bloon->GetColor() != "gone"){
                    cout << "The bloon is now " << bloon->GetColor() << endl;// The bloon is now Red
                    }
                }
                //increment money
                m_curMoney += totalPops*EARN_POP;
            }
        }
    }
}




void Game::RemovePopped() { //deallocation
  for (unsigned int i = 0; i < m_bloons.size();) {
    if (m_bloons[i]->GetHealth() <= 0) {
      delete m_bloons[i];
      m_bloons.erase(m_bloons.begin() + i);
    } else {
      ++i;
    }
  }
}



void Game::MoveBloons() { //move bloons along the path
    for (Bloon* bloon : m_bloons) {
        if (bloon->GetHealth() > 0) {
            bloon->SetLocation(bloon->GetLocation() + 1);
        }
    }
}



void Game::CheckPath() { //check the path to see if health should be reduced 
  for (unsigned int i = 0; i < m_bloons.size();) {
    if (m_bloons[i]->GetLocation() >= PATH_LENGTH) {
      m_curLife -= m_bloons[i]->GetHealth();
      cout << "A bloon made it to the end of the path and you took " << m_bloons[i]->GetHealth() << " damage." << endl;
      delete m_bloons[i];
      m_bloons.erase(m_bloons.begin() + i);
    } else {
      ++i;
    }
  }
}
