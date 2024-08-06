// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Monster driver

#include "Monster.h"
using namespace std;

Monster::Monster() {
    name_ = "";
    challenge_rating_ = 0;
}
Monster::Monster(string name, int challenge_rating) {
    name_ = name;
    challenge_rating_ = challenge_rating;
}
int Monster::getMonsterCR() {
    return challenge_rating_;
}
string Monster::getMonsterName() {
    return name_;
}
void Monster::setMonsterCR(int challenge_rating) {
    challenge_rating_ = challenge_rating;
}
void Monster::setMonsterName(string name) {
    name_ = name;
}

int findRandMonster (vector<Monster> monster, int cr) {
    int starting_index=0, num_monsters_at_cr = 0;
    bool check = false;
    
    for (int i=0; i<monster.size(); i++) {
        if (monster.at(i).getMonsterCR() == cr) {
            if (check == false) {
                check = true;
                starting_index = i;
            }
            num_monsters_at_cr++;
        }
    }
    if (check != true) {
        return -1;
    }
    return randomNum((starting_index + num_monsters_at_cr) - starting_index) -1;
}

vector<Monster> eraseMonster(vector<Monster> monster, int index) {
    monster.erase(monster.begin()+index);
    return monster;
}

