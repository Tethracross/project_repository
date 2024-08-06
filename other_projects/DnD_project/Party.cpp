// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Party driver

#include "Party.h"
using namespace std;

void Party::Character() {
    //Set a random name
}
void Party::Character(string name) {
    name_ = name;
    weapon_ = "";
    armor_ = false;
    fullness_ = 100;
}
string Party::getName() {
    return name_;
}
string Party::getWeapon() {
    return weapon_;
}
bool Party::getArmor() {
    return armor_;
} 
int Party::getFullness() {
    return fullness_;
}
int Party::getWeaponDamage() {
    if (weapon_ == "C") { // club
        return 0;
    }
    else if (weapon_ == "S") { // spear
        return 0;
    }
    else if (weapon_ == "R") { // rapier (+1)
        return 1;
    }
    else if (weapon_ == "BA") { // battle axe (+2)
        return 2;
    }
    else if (weapon_ == "LS") { // long sword (+3)
        return 3;
    }
    else return -1;
}
// int Character::getPartySize() {
//     return party_.size();
// }
// Character Character::getCharecterAt(int index) {
//     return party_.at(index);
// }
void Party::setWeapon(string weapon) {
    weapon_ = weapon;
}
void Party::setArmor(bool armor) {
    armor_ = armor;
}
void Party::setFullness(int fullness) {
    fullness_ =  fullness;
}