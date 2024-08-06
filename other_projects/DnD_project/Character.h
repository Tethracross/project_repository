// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Party header

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
using namespace std;

class Character {
private:
    string name_;
    string weapon_;
    bool armor_;
    int fullness_;

public:
    //vector<Character> party_; // --> this vector will go into main driver, not Party header 
    Character(); //random name    /starts with no armor or weapon
    Character(string name); //set name    /starts with no armor or weapon
    string getName();
    string getWeapon();
    bool getArmor();
    int getWeaponDamage(); //returns the additonal damage of equiped weapon
    int getFullness();
    // int getPartySize();
    // Character getCharecterAt(int index); --> goes in main driver
    void setWeapon(string weapon);
    void setArmor(bool armor);
    void changeFullness(int fullness);
    void setFullness(int fullness);
}; 

int getPartyDamage(vector<Character> party);
int randomNum(int range);
int getPartyArmor(vector<Character> party);

#endif