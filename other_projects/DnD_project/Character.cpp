// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Party driver

#include "Character.h"

using namespace std;

Character::Character() {
    //Set a random name
    weapon_ = "Hands";
    armor_ = false;
    fullness_ = 50;
}
Character::Character(string name) {
    name_ = name;
    weapon_ = "Hands";
    armor_ = false;
    fullness_ = 50;
}
string Character::getName() {
    return name_;
}
string Character::getWeapon() {
    return weapon_;
}
bool Character::getArmor() {
    return armor_;
}
int Character::getFullness() {
    return fullness_;
}
int Character::getWeaponDamage() {
    if (weapon_ == "Club" || weapon_ == "Spear") { // club or spear (+0)
        return 1;
    }
    else if (weapon_ == "Rapier") { // rapier (+1)
        return 2;
    }
    else if (weapon_ == "Battle-Axe") { // battle axe (+2)
        return 3;
    }
    else if (weapon_ == "Longsword") { // long sword (+3)
        return 4;
    }
    else {
        return 0; //empty handed (-1)
    }
}
void Character::setWeapon(string weapon) {
    weapon_ = weapon;
}
void Character::setArmor(bool armor) {
    armor_ = armor;
}
void Character::changeFullness(int fullness) {
    fullness_ +=  fullness;
}
void Character::setFullness(int fullness) {
    fullness_ = fullness;
}

int varietyBonus(vector<Character> party) {
    for (int i=0; i<party.size(); i++) {
        for (int j=0; j<party.size(); j++) {
            if (party.at(i).getName() == party.at(j).getName()) {
                break;
            }
            else if (party.at(i).getWeapon() == party.at(j).getWeapon()) {
                return 0;
            }
        }
    }
    return 4;
}
int getPartyDamage(vector<Character> party) {
    int damage=0;
    for (int i=0; i<party.size(); i++) {
        damage += party.at(i).getWeaponDamage();

    } 
    return damage + varietyBonus(party);
}
int getPartyArmor(vector<Character> party) {
    int num_armor;
    for (int i=0; i<party.size(); i++) {
        num_armor += party.at(i).getArmor();
    }
    return num_armor;
}
