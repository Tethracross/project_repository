// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 Driver

#include <iostream>
#include <vector>
#include <cmath>
#include "split.h"
#include "Map.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "Inventory.h"
using namespace std;

void printMenuLine() {
    cout << "_____________________________________________________________________________\n\n";
}

int mainMenu() {
    int difficulty;
    char input_char;
    int input;

    cout << R"(|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||)" << "\n\n" << 
            R"( _____                                       ______                          )" << "\n" <<
            R"(|  __ \                                     |  ____|                         )" << "\n" <<
            R"(| |  | |_   _ _ __   __ _  ___  ___  _ __   | |__   ___  ___ __ _ _ __   ___ )" << "\n" <<
            R"(| |  | | | | | '_ \ / _` |/ _ \/ _ \| '_ \  |  __| / __|/ __/ _` | '_ \ / _ \)" << "\n" <<
            R"(| |__| | |_| | | | | (_| |  __/ (_) | | | | | |____\__ \ (_| (_| | |_) |  __/)" << "\n" <<
            R"(|_____/ \__,_|_| |_|\__, |\___|\___/|_| |_| |______|___/\___\__,_| .__/ \___|)" << "\n" <<
            R"(                     __/ |                                       | |         )" << "\n" <<
            R"(                    |___/                                        |_|         )" << "\n\n" <<
            R"(|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||)" << "\n\n";

    do {
        cout << "Start (S)    Exit (E)" << endl;
        cin >> input_char;

        if (toupper(input_char) == 'E') {
            cout << "Good Bye!";
            return -1;
        }
        else if (toupper(input_char) != 'S') {
            cout << "Invalid Input: " << input_char << endl;
            printMenuLine();
        }
        else {
            break;
        }
    }
    while (input_char != 'S');
    printMenuLine();
    do {
        cout << "Choose your difficulty: 1 (story), 2 (easy), 3 (medium), 4 (hard)" << endl;
        cin >> input;
        if (input < 1 || input > 4) {
            cout << "Invalid Input: " << input << endl;
            printMenuLine();
        }
        else {
            cout << "You have chosen ";
            switch (input) {
            case 1:
                cout << "story mode" << endl;
                difficulty = 1;
                break;
            case 2:
                cout << "easy difficulty" << endl;
                difficulty = 2;
                break;
            case 3:
                cout << "medium difficulty" << endl;
                difficulty = 3;
                break;
            case 4:
                cout << "hard difficulty" << endl;
                difficulty = 4;
                break;

            default:
                cout << "FATAL ERROR";
                return -2;
            }
            printMenuLine();
        }
    }
    while (input < 1 || input > 4);
    return difficulty;
}

string randomName();

int main() {
    int input, difficulty;
    int menu_level=0; //0 main menu, 1..., 2..., 
    string input_string;

    //main menu
    difficulty = mainMenu();
    if (difficulty <= -1) {
        return 0;
    }

    //plot
    cout << "intro plot, why your here and what your doing" << endl;
    printMenuLine();

    //Making the Party
    int party_size = 5 - difficulty/2;
    Character party[party_size]; //variable party size based on difficulty (5 story, 4 easy, 4 medium, 3 hard)
    cout << "What is your adventurers name?" << endl;
    cin >> input_string;
    if (input_string.length() > 0) {
        party[0] = Character(input_string);
    }
    else {
        // Character(randomName());
    }
    cout << "PROCESSED CHARACTER: " << party[0].getName() << endl; //temp line of code
    
    cout << "What is the name of your companions?" << endl;
    for (int i=1; i<party_size; i++) {
        cin >> input_string;
        if (input_string.length() > 0) {
            party[i] = Character(input_string);
        }
        else {
            // Character(randomName());
        }
    }
    cout << "PROCESSED CHARACTERS: ";
    for (int i=1; i<party_size; i++) { //temp line of code
        cout << party[i].getName() << " ";
    }

    //Gameplay Loop
    do {
    /*
    main game loop
    */
    }
    while (toupper(input) != 'E');
}