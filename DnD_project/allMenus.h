// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - All Menus header

#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <cmath>
#include "InvenMap.h"
using namespace std;

int getNum(string str);
void printMenuLine();
void printParty(vector<Character> party, int size);
void printInventory(Inventory Inventory);
int mainMenu();
Inventory wantToPurchase(int index_of_item, string for_ingredients_or_armor, string for_armor_only, int input, int normal_price, float price_modifier, Inventory inventory);
Inventory buyingItemMenu(int index_of_item, int normal_price, float price_modifier, Inventory inventory);
Inventory merchantMenu(Inventory inventory, float price_modifier);
void statusUpdate (Inventory inventory, vector<Character> party, int rooms_cleared, int anger_level);
InvenMap equipmentMenu(InvenMap inven_map);
InvenMap misfortune (InvenMap inven_map); //retuns the number of the misfortune (robbery 1, tools break 2, food poisoning 3, lost party member 4)
InvenMap investigate (InvenMap inven_map, int rooms_cleared);
InvenMap actionMenu(InvenMap inven_map, int rooms_cleared, int anger_level, vector<Monster> monster);
int randomNum(int range);
InvenMap cookingMenu(InvenMap inven_map);

#endif