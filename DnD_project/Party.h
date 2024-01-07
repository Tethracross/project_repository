// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Party header

#include <iostream>
#include <vector>
#include "Inventory.h"
using namespace std;

class Party {
private:
    string name_;
    string weapon_;
    bool armor_;
    int fullness_;
    vector<Inventory> items_; 

public: 
    //vector<Character> party_; // --> this vector will go into main driver, not Party header 
    void Character(); //random name    /starts with no armor or weapon
    void Character(string name); //set name    /starts with no armor or weapon
    string getName();
    string getWeapon();
    bool getArmor();
    int getWeaponDamage();
    int getFullness();
    // int getPartySize();
    // Character getCharecterAt(int index); --> goes in main driver
    void setWeapon(string weapon);
    void setArmor(bool armor);
    void setFullness(int fullness);
};
