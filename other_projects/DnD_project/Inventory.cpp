// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Inventory driver

#include "Inventory.h"
using namespace std;

Inventory::Inventory() {
    gold_ = 0;
    //Cookware
    items_[0] = Item("Cookware", "Pot", 0);
    items_[1] = Item("Cookware", "Frying Pan", 0);
    items_[2] = Item("Cookware", "Cauldron", 0);
    //Weapons
    items_[3] = Item("Weapon", "Club", 0);
    items_[4] = Item("Weapon", "Spear", 0);
    items_[5] = Item("Weapon", "Rapier", 0);
    items_[6] = Item("Weapon", "Battle-Axe", 0);
    items_[7] = Item("Weapon", "Longsword", 0);
    //Treasures
    items_[8] = Item("Treasure", "R", 0);
    items_[9] = Item("Treasure", "N", 0);
    items_[10] = Item("Treasure", "B", 0);
    items_[11] = Item("Treasure", "C", 0);
    items_[12] = Item("Treasure", "G", 0);
}
Inventory::Inventory(int gold_amount) {
    gold_ = gold_amount;
    //Cookware
    items_[0] = Item("Cookware", "Pot", 0);
    items_[1] = Item("Cookware", "Frying Pan", 0);
    items_[2] = Item("Cookware", "Cauldron", 0);
    //Weapons
    items_[3] = Item("Weapon", "Club", 0);
    items_[4] = Item("Weapon", "Spear", 0);
    items_[5] = Item("Weapon", "Rapier", 0);
    items_[6] = Item("Weapon", "Battle-Axe", 0);
    items_[7] = Item("Weapon", "Longsword", 0);
    //Treasures
    items_[8] = Item("Treasure", "R", 0);
    items_[9] = Item("Treasure", "N", 0);
    items_[10] = Item("Treasure", "B", 0);
    items_[11] = Item("Treasure", "C", 0);
    items_[12] = Item("Treasure", "G", 0);
}
void Inventory::addItem(int index, int amount) {
    items_[index].increaseNum(amount);
}
bool Inventory::readItem(string file_name) {
    //read file add to items_ vector
    return false;
}
void Inventory::addGold(int amount) {
    gold_ += amount;
}
void Inventory::addIngredients(int amount) {
    ingredients_ += amount;
}
int Inventory::getItemNum(int index) {
    return items_[index].getNum();
}
int Inventory::getItemIndex(string type, string item) {
    for (int i=0; i<13; i++) {
        if (items_[i].getType() == type) {
            if (items_[i].getItemName() == item) {
                return i;
            }
        }
    }
    return -1;
}
int Inventory::getGold() {
    return gold_;
}
int Inventory::getIngredients() {
    return ingredients_;
}
int Inventory::getKeys() {
    return keys_;
}
Item Inventory::getItem(int index) {
    return items_[index];
}
int Inventory::getArmor() {
    return armors_;
}
void Inventory::addArmor(int amount) {
    armors_+=amount;
}
void Inventory::addKeys(int amount) {
    keys_ += amount;
}
void Inventory::setGold(int amount) {
    gold_ = amount;
}
void Inventory::breakBestCookWare() {
    int best_index=0;
    for (int i=1; i<3; i++) {
        if (items_[i].getNum() >= 0 && i > best_index) {
            best_index = i;
        }
    }
    switch (best_index)
    {
    case 0:
        if (randomNum(4) == 1) {
            items_[0].increaseNum(-1);
            cout << "\nOh no! Your Pot broke." << endl;
        }
        break;
    case 1:
        if (randomNum(10) == 1) {
            items_[1].increaseNum(-1);
            cout << "\nOh no! Your Pan broke." << endl;
        }
        break;
    case 2:
        if (randomNum(50) == 1) {
            items_[2].increaseNum(-1);
            cout << "\nOh no! Your Cauldron broke." << endl;
        }
        break;
    default:
        break;
    }
}