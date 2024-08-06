// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 Driver

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "allMenus.h"
#include "split.h"
#include "Map.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "Inventory.h"
#include "InvenMap.h"
using namespace std;

/*
prints a line
*/
void printMenuLine() {
    cout << "_____________________________________________________________________________\n\n";
}

/*
Outputs a random number from 1 to an upper bound
input: int range (upper bound)S
*/
int randomNum(int range) {
    int prob = rand()%range + 1;
    return prob;
}

string randomName(int random_num, string names[]) {
    return names[random_num];
}

/*
input: string str
checks if input string starts with a number
if so it reaturns the stoi of the string
*/
int getNum(string str) {
    if (!isdigit(str[0])) {
        return -1;
    }
    return stoi(str);
}

int main() {
    int input, difficulty, starting_gold=125, rooms_cleared=0, anger_level=0;
    int menu_level=0; // 0 main menu, 1..., 2..., 
    bool playing = false;
    int num_names = 4947; //num names
    string input_string, line, names_arr[num_names], names_file = "names.txt", monster_temp[2], monsters_file = "Monster.txt";
    ifstream read_names(names_file), read_monsters(monsters_file);
    srand(time(NULL));

    //get random name list
    if (read_names.is_open()) {
        //while file is open
        int i=0;
        while (getline(read_names, line)) {
            names_arr[i] = line;
            i++;
        }
    }
    read_names.close();

    //Gameplay Loop
    do {
        //main menu
        difficulty = mainMenu();
        if (difficulty <= 0) {
            return 0;
        }
        else {
            playing = true;
        }

        //initializing inventory with gold amount based on difficulty
        Inventory inventory(starting_gold-(difficulty-1)*25);        

        //make monsters array
        vector<Monster> monsters;
        if (read_monsters.is_open()) {
            //while file is open
            int i=0;
            while (getline(read_monsters, line)) {
                split(line, ',', monster_temp, 2);
                monsters.push_back(Monster(monster_temp[0], stoi(monster_temp[1])));
            }
        }
        read_monsters.close();

        //Making the Party
        int party_size = 5 - difficulty/4; //variable party size based on difficulty (5 story, 5 easy, 5 medium, 4 hard)
        vector<Character> party;
        Character party_permanent[party_size];
        party.clear();

        cout << "What is your adventurers name? ('r' for a random name) \n\n> ";
        cin >> input_string;
        if (input_string != "r" && input_string != "R") {
            party.push_back(Character(input_string));
            party_permanent[0] = Character(input_string);
        }    
        else {
            party.push_back(Character(randomName(randomNum(num_names), names_arr)));
            party_permanent[0] = Character(input_string);
            cout << "Random name chosen." << endl;
        }

        cout << "\nPROCESSED CHARACTER: " << party.at(0).getName() << endl; //temp code
    
        cout << "\nWhat are the names of your " << party_size-1 << " companions? (one per-line) ('r' for a random name)\n\n";
        for (int i=1; i<party_size; i++) {
            cout << "> ";
            cin >> input_string;
            if (input_string != "r" && input_string != "R") {
                party.push_back(Character(input_string));
                party_permanent[i] = Character(input_string);
            }
            else {
                for (int j=i; j<party_size; j++) {
                    party.push_back(Character(randomName(randomNum(num_names), names_arr)));
                    party_permanent[j] = Character(input_string);
                }
                cout << "Random names chosen." << endl;
                break;
            }
        }
        cout << "\nPROCESSED CHARACTERS: "; //temp code
        for (int i=1; i<party_size; i++) { 
            cout << party.at(i).getName() << " ";
        }
        cout << endl;
        printMenuLine();

        Map map;
        map.setMap();
        InvenMap inven_map(map, inventory, party, monsters);
        // inven_map.setMap(setMap(map));

        //plot
        cout << "Between the " << party_size << " of you, you have " << inventory.getGold() << " gold pieces.\n"  
                "You will need to spend the some of your money on the following items:\n\n"
                " - INGREDIENTS. To make food, you have to cook raw ingredients.\n"
                " - COOKWARE. If you want to cook, you have to have cookware first.\n"
                " - WEAPONS. You'll want at least one weapon per party member to fend off monsters (Having a large variety of weapons will help you fend off monsters).\n"
                " - ARMOR. Armor increases the chances of surviving a monster attack.\n\n"
                "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way.\n"
                "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
        printMenuLine();

        //merchant menu
        inven_map.setInven(merchantMenu(inventory, 1)); //1 is the price modifier, changes how expensive the merchant is
        inven_map.updateInvenMap(actionMenu(inven_map, rooms_cleared, anger_level, monsters));
        if (inven_map.getLife()) {
            cout << R"(___________________________________________________)" << "\n" << 
                    R"(__     ______  _    _  __          ______  _   _ _ )" << "\n" <<  
                    R"(\ \   / / __ \| |  | | \ \        / / __ \| \ | | |)" << "\n" << 
                    R"( \ \_/ / |  | | |  | |  \ \  /\  / / |  | |  \| | |)" << "\n" << 
                    R"(  \   /| |  | | |  | |   \ \/  \/ /| |  | | . ` | |)" << "\n" << 
                    R"(   | | | |__| | |__| |    \  /\  / | |__| | |\  |_|)" << "\n" << 
                    R"(   |_|  \____/ \____/      \/  \/   \____/|_| \_(_))" << "\n" <<
                    R"(___________________________________________________)" << "\n";
            printMenuLine();
        }

    } while (playing==true);
    return 0;
}

// g++ -std=c++17 .\DungeonEscapeDriver.cpp .\Character.cpp .\Inventory.cpp .\Item.cpp .\Map.cpp .\Monster.cpp .\split.cpp .\allMenus.cpp .\InvenMap.cpp
// .\a.exe