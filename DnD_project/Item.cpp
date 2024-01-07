// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - Item header

#include <iostream>
#include "Item.h"
using namespace std;

Item::Item(string type, string item_identifier, int num_items) {
    type_ = type;
    item_identifier_ = item_identifier;
    num_of_item_ = num_items;
}
string Item::getType() {
    return type_;
}
string Item::getItemName() {
    return item_identifier_;
}
int Item::getNum() {
    return num_of_item_;
}
void Item::increaseNum(int amount) {
    num_of_item_+= amount;
}
Item::Item() {
    type_ = "";
    item_identifier_ = "";
    num_of_item_ = -1;
}
void Item::setItemNum(int amount) {
    num_of_item_ = amount;
}