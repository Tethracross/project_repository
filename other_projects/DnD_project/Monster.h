// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Monster header

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "Character.h"

using namespace std;

class Monster {
private:
    string name_;
    int challenge_rating_;
    
public:
    Monster(); 
    Monster(string name, int challenge_rating);
    string getMonsterName();
    int getMonsterCR();
    void setMonsterName(string name);
    void setMonsterCR(int challenge_rating);
};

vector<Monster> eraseMonster(vector<Monster> monsters, int index); // will erase monster from Monster.txt file if party wins battle
int findRandMonster(vector<Monster> monsters, int challenge_rating);

#endif