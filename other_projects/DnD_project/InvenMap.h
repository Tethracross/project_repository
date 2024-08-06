#ifndef INVENMAP_H
#define INVENMAP_H

#include <iostream>
#include "Map.h"
#include "Inventory.h"
#include "Monster.h"
using namespace std;

class InvenMap {
private:
    Map map_;
    Inventory inventory_;
    vector<Character> party_;
    vector<Monster> monster_;
    bool life_ = true;
public:
    InvenMap(Map map, Inventory inventory, vector<Character> party, vector<Monster> monster_);
    void updateInvenMap(InvenMap inven_map);
    void updateInvenMap(Map map_, Inventory inventory_, vector<Character> party_, vector<Monster> monster_);
    void setMap(Map map);
    void setInven(Inventory inventory);
    Map getMap();
    Inventory getInven();
    void setPos(int arr[2]);
    void setParty(vector<Character> party);
    vector<Character> getParty();
    void setMonster(vector<Monster> monster);
    vector<Monster> getMonster();
    void setLife(bool life);
    bool getLife();
};

void printMenuLine();
InvenMap loseFight(InvenMap inven_map, int index_rand_monster);
InvenMap fightMonster(InvenMap inven_map, int cr); // story mode monster attack
InvenMap misfortune (InvenMap inven_map);

#endif