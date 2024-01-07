// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Inventory header

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Item.h"

using namespace std;

class Inventory { 
private:
    int gold_;
    int ingredients_ = 0;
    int armors_ = 0;
    int keys_ = 0;
    const static int total_items_ = 13; //total number of items in game
    Item items_[total_items_]; 

public:
    Inventory();
    Inventory(int difficulty); //makes inventory with an amount of gold based on difficulty
    int getItemNum(int item_index);
    int getItemIndex(string type, string item);
    int getIngredients(); 
    int getGold(); 
    int getArmor();
    int getKeys();
    Item getItem(int item_index);
    void addItem(int item_index, int amount); //return true if added false if not
    bool readItem(string file_name);
    void addGold(int amount); //can be used to add or remove gold
    void addIngredients(int amount);
    void addArmor(int amount);
    void addKeys(int amount);
    void setGold(int amount);
    void breakBestCookWare();
};

int randomNum(int range);

#endif