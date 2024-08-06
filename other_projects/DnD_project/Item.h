// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Item header

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;

class Item {
private:
    string type_;
    string item_identifier_;
    int num_of_item_;

public:
    Item(string type, string item_identifier, int num_of_item);
    Item();
    string getType();
    string getItemName();
    int getNum();
    void increaseNum(int amount); //can be used to increase or decrease amount
    void setItemNum(int amount);
};

#endif