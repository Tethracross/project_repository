#include "InvenMap.h"
using namespace std;

InvenMap::InvenMap(Map map, Inventory inventory, vector<Character> party, vector<Monster> monster) {
    map_ = map;
    inventory_ = inventory;
    party_ = party;
    monster_ = monster;
}

bool InvenMap::getLife() {
    return life_;
}
void InvenMap::setLife(bool life) {
    life_=life;
}
void InvenMap::updateInvenMap(InvenMap inven_map) {
    map_ = inven_map.getMap();
    inventory_ = inven_map.getInven();
    party_ = inven_map.getParty();
    monster_ = inven_map.getMonster();
}
void InvenMap::updateInvenMap(Map map, Inventory inventory, vector<Character> party, vector<Monster> monster) {
    map_ = map;
    inventory_ = inventory;
    party_ = party;
    monster_ = monster;
}
void InvenMap::setMap(Map map) {
    map_ = map;
}
void InvenMap::setInven(Inventory inventory) {
    inventory_ = inventory;
}
Map InvenMap::getMap() {
    return map_;
}
Inventory InvenMap::getInven() {
    return inventory_;
}
void InvenMap::setPos(int arr[]) {
    map_.setPlayerPosition(arr[0], arr[1]);
}
void InvenMap::setParty(vector<Character> party) {
    party_.resize(party.size());
    party_.swap(party);
}
vector<Character> InvenMap::getParty() {
    return party_;
}
void InvenMap::setMonster(vector<Monster> monster) {
    monster_.resize(monster.size());
    monster_.swap(monster);
}
vector<Monster> InvenMap::getMonster() {
    return monster_;
}

InvenMap loseFight(InvenMap inven_map, int index_rand_monster) {
    int index_lost = randomNum(inven_map.getParty().size()-1);
    vector<Character> party = inven_map.getParty();

    cout << "\nOh no! " << party.at(index_lost).getName() << " couldn't run from the " << inven_map.getMonster().at(index_rand_monster).getMonsterName() << "!" << endl;
    party.erase(party.begin() + index_lost);
    inven_map.setParty(party);

    return inven_map;
}

InvenMap fightMonster(InvenMap inven_map, int cr) {
    vector<Monster> monster = inven_map.getMonster();
    int index_rand_monster = findRandMonster(monster, cr);
    char input;
    bool death=false;
    vector<Character> party = inven_map.getParty();
    Inventory inventory = inven_map.getInven();
    
    if (cr>5) {cr=5;}
    if (index_rand_monster < 0) {
        cout << "\nThere appears to be no monsters around O-O" << endl;
        return inven_map;
    }
    else {
        cout  << "\n" << monster.at(index_rand_monster).getMonsterName() << " ahead!";
        if (getPartyDamage(party) == 0) {
            cout << " RUN (R)!!!" << endl;
        }
        else {
            cout << " FIGHT (F) OR RUN (R)!!!" << endl;
        }
    }
    
    for (int i=0; i<party.size(); i++) {
        int fullnessDrop = randomNum(2)-1;
        if (fullnessDrop == 0) {
            party.at(i).changeFullness(-1);
        }
    }

    do {
        cout << "\n> ";
        cin >> input;
        //if the party runs they automaticaly lose the fight
        if (toupper(input) == 'R') {
            if (party.size() <= 1) {
                cout << R"(__     ______  _    _    _____ _____ ______ _____  _ _ )" << "\n" <<
                        R"(\ \   / / __ \| |  | |  |  __ \_   _|  ____|  __ \| | |)" << "\n" <<
                        R"( \ \_/ / |  | | |  | |  | |  | || | | |__  | |  | | | |)" << "\n" <<
                        R"(  \   /| |  | | |  | |  | |  | || | |  __| | |  | | | |)" << "\n" <<
                        R"(   | | | |__| | |__| |  | |__| || |_| |____| |__| |_|_|)" << "\n" <<
                        R"(   |_|  \____/ \____/   |_____/_____|______|_____/(_|_))" << "\n\n";
                printMenuLine();
                inven_map.setLife(false);
                return inven_map;
            }
            inven_map.updateInvenMap(inven_map.getMap(), inventory, party, monster);
            inven_map.updateInvenMap(loseFight(inven_map, index_rand_monster));
            return inven_map;
        }
        else if (toupper(input) != 'F') {
            cout << "Invalid Input: " << input << endl;
        }
    } while (toupper(input) != 'F');

    int winOrLoss = (randomNum(6) * getPartyDamage(party)) - ((randomNum(6) * cr) / getPartyArmor(party));
    cout << winOrLoss << endl;

    if (winOrLoss > 0) {
        inventory.addGold((10/randomNum(5))*cr);
        inventory.addIngredients(5*cr);
        if (randomNum(10) == 1) { // 10% chance winning against a monster adds a key to party's inventory
            inventory.addKeys(1);
        }
        cout << "You killed the " << monster.at(index_rand_monster).getMonsterName() << "!" << "\n\n";
        monster = eraseMonster(monster, index_rand_monster);
        printMenuLine();
        inven_map.updateInvenMap(inven_map.getMap(), inventory, party, monster);
        return inven_map; // party wins battle
    }
    else {
        inventory.setGold(floor(inventory.getGold()/4)); // decrease party gold by 25% (truncated)
        inventory.addIngredients(-(6/(randomNum(6))*cr)); // decrease ingredients by (6/(randNum [1-6]))*cr
        for (int i=1; i < party.size(); i++) {
            if (randomNum(100) <= 10-5*party.at(i).getArmor()) {
                cout << "\nOh no! " << party.at(i).getName() << " couldn't run from the " << monster.at(index_rand_monster).getMonsterName() << "!" << "\n";
                party.erase(party.begin() + i);
            } 
        }
        printMenuLine();
        inven_map.updateInvenMap(inven_map.getMap(), inventory, party, monster);
        return inven_map; // party looses battle 
    }
}

InvenMap misfortune (InvenMap inven_map) { // need to add the alerts
    int if_event_happens = randomNum(100), which_event = randomNum(100), index, count=0, num, random;
    int possible_index[5];
    bool t_f=false, armor=false, weapon=false;
    Inventory inventory = inven_map.getInven();
    vector<Character> party = inven_map.getParty();
    Map map = inven_map.getMap();

    if (if_event_happens<=40) {//if misfortune happens
        if (which_event<=30) { //robbed
            random = randomNum(3);
            switch (random) {
            case 1: //loose ingredients
                num=randomNum(10)+5;
                if (num <= inventory.getIngredients()) {
                    inventory.addIngredients(-num);
                }
                else {
                    num = inventory.getIngredients();
                    inventory.addIngredients(-num);
                }
                printf("OH NO! Your team was robbed by dungeon bandits!\nYou lost %i kgs of ingredients!\n", num);
                printMenuLine();
                break;
            case 2: //loose cookware
                do {
                    index = randomNum(3)-1;
                    if (count>10) {
                        cout << "OH NO! Your team was robbed by dungeon bandits!\nLuckily they didnt find what they were looking for!" << endl;
                        break;
                    }
                    else if (inventory.getItemNum(index) > 0) {
                        t_f=true;
                        inventory.addItem(index, -1);
                        cout << "OH NO! Your team was robbed by dungeon bandits!\nYou lost 1 " << inventory.getItem(index).getItemName() << "!" << endl;
                    }
                    else {
                        t_f=false;
                        count++;
                    }
                } while (!t_f || count<=10);
                printMenuLine();
                break;
            case 3: //loose armor
                if (inventory.getArmor() > 0) {
                    inventory.addArmor(-1);
                }
                else {
                    do {
                        count=0;
                        index = randomNum(party.size())-1;
                        if (count > 10) {
                            cout << "OH NO! Your team was robbed by dungeon bandits!\nLuckily they didnt find what they were looking for!" << endl;
                            break;
                        }
                        else if (party.at(index).getArmor() == true) {
                            party.at(index).setArmor(false);
                            t_f=true;
                        }
                        else {
                            t_f=false;
                            count++;
                        }
                    } while (!t_f || count<=10);
                }
                cout << "OH NO! Your team was robbed by dungeon bandits!\nYou lost 1 suit of armor!" << endl;
                printMenuLine();
                break;
            default:
                break;
            }

        }
        else if (which_event>30 && which_event<=60) { //food poisoning
            int num=randomNum(10)+5;
            party.at(randomNum(party.size())-1).changeFullness(-num);
        }
        else if (which_event>60 && which_event<=90) {
            if (map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())) {
                for (int i=1; i < party.size(); i++) {
                    if (randomNum(10) <= 3) {
                        cout << "\nOh no! Your teamate " << party.at(i).getName() << " is trapped in the previous room and is unable to get through. You must continue without them." << "\n";
                        party.erase(party.begin() + i);
                        break;
                    } 
                }
            }
        }
        else {
            if (inventory.getArmor()>0) {
                armor=true;
            }
            for (int i=3; i<8; i++) {
                if (inventory.getItemNum(i)>0) {
                    weapon=true;
                    possible_index[count] = i;
                    count++;
                }
            }
            if (armor && weapon) {
                random = randomNum(2);
                switch (random)
                {
                case 1:
                    inventory.addArmor(-1);
                    cout << "Oh no! A suit of armor broke!" << endl;
                    break;
                case 2:
                    random = randomNum(count);
                    inventory.addItem(possible_index[random], -1);
                    cout << "Oh no! A " << inventory.getItem(possible_index[random]).getItemName() << " broke!" << endl;
                    break;
                default:
                    break;
                }
                printMenuLine();
            }
            else if (armor) {
                inventory.addArmor(-1);
                cout << "Oh no! A suit of armor broke!" << endl;
                printMenuLine();
            }
            else if (weapon) {
                random = randomNum(count)-1;
                inventory.addItem(possible_index[random], -1);
                cout << "Oh no! A " << inventory.getItem(possible_index[random]).getItemName() << " broke!" << endl;
                printMenuLine();
            }
            else {
                for (int i=0; i<party.size(); i++) {
                    if (party.at(i).getWeapon() != "Hands") {
                        weapon=true;
                        possible_index[count] = i;
                        count++;
                    }
                }
                if (weapon) {
                    random = randomNum(count)-1;
                    cout << "Oh no! " << party.at(random).getName() << "'s " << party.at(random).getWeapon() << "broke!" << endl;
                    party.at(random).setWeapon("Hands");
                    printMenuLine();
                }
            }
        }
    }
    inven_map.updateInvenMap(inven_map.getMap(), inventory, party, inven_map.getMonster());
    return inven_map;
}