// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 - All Menus driver


#include "allMenus.h"
using namespace std;

/*
Prints out the party member names and their fullness
input: vector<Character> party, int size
*/
void printParty(vector<Character> party) {
    cout << "+-------------+" << endl <<
            "| PARTY       |" << endl <<
            "+-------------+" << endl;
    for (int i=0; i<party.size(); i++) {
        cout << "| " << party.at(i).getName() << " | Fullness: " << party.at(i).getFullness() <<
               " | Weapon: " << party.at(i).getWeapon() << " | Armor: " << party.at(i).getArmor() << endl;
    }
}

/*
Prints out the parties inventory
input: Inventory inventory
*/
void printInventory(Inventory inventory) {
    cout << "+-------------+" << endl <<
            "| INVENTORY   |" << endl <<
            "+-------------+" << endl <<
            "| Gold        | " << inventory.getGold() << endl <<
            "| Ingredients | " << inventory.getIngredients() << " kg" << endl <<
            "| Cookware    | Pot: " << inventory.getItemNum(0) <<
                            " | Pan: " << inventory.getItemNum(1) <<
                            " | Cauldron: " << inventory.getItemNum(2) << endl <<
            "| Weapons     | Club: " << inventory.getItemNum(3) <<
                            " | Spear: " << inventory.getItemNum(4) <<
                            " | Rapier: " << inventory.getItemNum(5) <<
                            " | Battle Axe: " << inventory.getItemNum(6) <<
                            " | Longsword: " << inventory.getItemNum(7) << endl <<
            "| Armor       | " << inventory.getArmor() << endl <<
            "| Treasures   | Ring: " << inventory.getItemNum(8) <<
                            " | Necklace: " << inventory.getItemNum(9) << 
                            " | Bracelet: " << inventory.getItemNum(10) <<
                            " | Circlet: " << inventory.getItemNum(11) <<
                            " | Goblet: " << inventory.getItemNum(12) << endl;
}

/*
Opens and prints main menu
no inputs
lets users start and exit the game
lets users choose their difficulty
repeats until valid input
returns difficulty to update main
if difficulty=0 close the game;
*/
int mainMenu() {
    int difficulty;
    string input_string;
    char input;
    
    cout << R"(|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||)" << "\n\n" << 
            R"( _____                                       ______                          )" << endl <<
            R"(|  __ \                                     |  ____|                         )" << endl <<
            R"(| |  | |_   _ _ __   __ _  ___  ___  _ __   | |__   ___  ___ __ _ _ __   ___ )" << endl <<
            R"(| |  | | | | | '_ \ / _` |/ _ \/ _ \| '_ \  |  __| / __|/ __/ _` | '_ \ / _ \)" << endl <<
            R"(| |__| | |_| | | | | (_| |  __/ (_) | | | | | |____\__ \ (_| (_| | |_) |  __/)" << endl <<
            R"(|_____/ \__,_|_| |_|\__, |\___|\___/|_| |_| |______|___/\___\__,_| .__/ \___|)" << endl <<
            R"(                     __/ |                                       | |         )" << endl <<
            R"(                    |___/                                        |_|         )" << "\n\n" <<
            R"(|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||)" << "\n\n";

    do {
        cout << "Start (S)   Exit (E)\n\n> ";
        cin >> input_string;
        input = input_string[0];

        if (toupper(input) == 'E') {
            cout << "\nGood Bye!";
            return 0;
        }
        else if (toupper(input) != 'S') {
            cout << "\nInvalid Input: " << input_string << "\n\n";
            printMenuLine();
        }
    } while (toupper(input) != 'S');

    printMenuLine();

    do {
        cout << "Choose your difficulty: 1 (story), 2 (easy), 3 (medium), 4 (hard)\n\n> " ;
        cin >> input_string;
        input = input_string[0];
        switch (input) {
        case '1':
            cout << "\nYou have chosen story mode" << endl;
            difficulty = 1;
            break;
        case '2':
            cout << "\nYou have chosen easy difficulty" << endl;
            difficulty = 2;
            break;
        case '3':
            cout << "\nYou have chosen medium difficulty" << endl;
            difficulty = 3;
            break;
        case '4':
            cout << "\nYou have chosen hard difficulty" << endl;
            difficulty = 4;
            break;
        default:
            cout << "\nInvalid Input: " << input_string << "\n\n";
            break;
        }
        printMenuLine();
    } while (input < '1' || input > '4');
    return difficulty;
}

int getTotalTreasurePrice(float price_modifier, Inventory inventory) {
    int sum=0;
    for (int index=8; index<13; index++) {
        sum += inventory.getItemNum(index) * price_modifier * (index-7)*10;
    }
    return sum;
}

/*
Sub menu of buyingItemMenu
input: int index_of_item, string for_ingredients_or_armor, string for_armor_only, int input, int normal_price, float price_modifier, Inventory inventory
Lets the player decide if they want to purchase
repeates until valid input
returns inventory to update buyingItemMenu
*/
Inventory wantToPurchase(int index_of_item, string for_ingredients_or_armor, string for_armor_only, int input, int normal_price, float price_modifier, Inventory inventory) {
    char input_char;
    string input_string;

    do {
        if (index_of_item <= 12) {
            cout << "\nDo you want to buy " << input << " " << inventory.getItem(index_of_item).getItemName() << "(s) for " << 
                    (int)ceil(input*price_modifier*normal_price) << " Gold? (y/n)\n\n> ";
        }
        else {
            cout << "\nDo you want to buy " << input << " " << for_ingredients_or_armor << "(s) " << for_armor_only << " for " << 
                    (int)ceil(input*price_modifier*normal_price) << " Gold? (y/n)\n\n> ";
        }

        cin >> input_string;
        input_char=input_string[0];
        
        if (toupper(input_char) == 'Y') {
            if (inventory.getGold() >= input*price_modifier*normal_price) {
                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                inventory.addGold(-input*price_modifier*normal_price);

                if (index_of_item == 13) {
                    inventory.addIngredients(input);
                }
                else if (index_of_item == 14) {
                    inventory.addArmor(input);
                }
                else {
                    inventory.addItem(index_of_item, input);
                }
                return inventory;
            }
            else {
                printf("\nSorry you dont have enough gold. You are %i gold short.\n", (int)ceil(input*price_modifier*normal_price)-inventory.getGold());
                break;
            }
        }
        else if (toupper(input_char) != 'N') {
            cout << "\nInvalid Input: " << input_string << "\n\n";
        }
        else {
            break;
        }
    } while (toupper(input_char) != 'Y');

    return inventory;
}

/*
Sub menu of merchantMenu, asks how many of an item you wish to buy
uses getNum and wantToPurchase
input: int index_of_item, int normal_price, float price_modifier, Inventory inventory
lets the player choose how much of an item they want
returns inventory to update merchantMenu
*/
Inventory buyingItemMenu(int index_of_item, int normal_price, float price_modifier, Inventory inventory) {
    int input;
    string input_string;

    do {
        cout << "\nHow many " << inventory.getItem(index_of_item).getItemName() << "s would you like? [" << (int)ceil(price_modifier*normal_price) << "/per] (0 to cancel)\n\n> ";
        cin >> input_string;
        input = getNum(input_string);
        if (input == 0) {
            break;
        }
        else if (input > 0) {
            inventory = wantToPurchase(index_of_item, "", "", input, normal_price, price_modifier, inventory);
        }
        else {
            cout << "\nInvalid Input: " << input_string << "\n\n";
        }
    } while (input < 0);
    
    return inventory;
}

/*
Opens and prints Merchant Menu
Uses getNum, buyingItemMenu, and wantToPurchase
input: Inventory inventory, float price_modifier  //price modifier changes how expensive the merchant is
Displays inventory and gold amount, lets the player buy items with gold and sell treasures for gold
Repeats until player chooses to quit
returns inventory to update inventory inventory in main
*/
Inventory merchantMenu(Inventory inventory, float price_modifier) {
    int input, input_outer, total_sell;
    char input_char;
    string input_string;
    int price_ingredient=1, price_pot=2, price_pan=10, price_Cauldron=20, price_club=2, price_spear=2, price_rapier=5, price_ax=15, price_sword=50, price_armor=5;

    cout << "If you're looking to get supplies, you've come to the right place." << endl <<
    "I would be happy to part with some of my wares...for the proper price!" << "\n\n";

    do {
        //print inventory
        printInventory(inventory);
        cout << "+-------------+" << "\n\n";
                
        //display choices
        cout << "Choose one of the following:" << endl <<
                " 1. Buy Ingredients: To make food, you have to cook raw ingredients." << endl <<
                " 2. Buy Cookware: You will need something to cook those ingredients." << endl <<
                " 3. Buy Weapons: It's dangerous to go alone, take this!" << endl <<
                " 4. Buy Armor: If you want to survive monster attacks, you will need some armor." << endl <<
                " 5. Sell Treasures: If you find anything shiny, I would be happy to take it off your hands."<< endl <<
                " 6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << "\n\n> ";
        cin >> input_string;
        input_outer = getNum(input_string);
        switch (input_outer) {
        //Ingredients
        case 1:
            do {
                printf("\nHow many kg of ingredients do you need [%.2f Gold/kg]? (0 to cancel)\n\n> ", price_modifier);
                cin >> input_string;
                input = getNum(input_string);
                if (input == 0) {
                    break;
                }
                else if (input > 0) {
                    inventory = wantToPurchase(13, "ingredient", "", input, price_ingredient, price_modifier, inventory);
                }
                else {
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                }
            } while (input < 0);

            printMenuLine();
            break;

        //Cookware
        case 2:
            do {
                cout << "\nI have a several types of cookware, which one would you like?" << endl <<
                        "Each type has a different probability of breaking when used, marked with (XX%)." << "\n\n" <<
                        "Choose one of the following:" << endl <<
                        " 1. (25%) Ceramic Pot [" << (int)ceil(price_modifier*price_pot) << " Gold]" << endl <<
                        " 2. (10%) Frying Pan [" << (int)ceil(price_modifier*price_pan) << " Gold]" << endl <<
                        " 3. ( 2%) Cauldron [" << (int)ceil(price_modifier*price_Cauldron) << " Gold]" << endl <<
                        " 4. Cancel" << "\n\n> ";
                cin >> input_string;
                input = getNum(input_string);
                switch (input) {
                case 1:
                    inventory = buyingItemMenu(0, price_pot, price_modifier, inventory);
                    break;
                case 2:
                    inventory = buyingItemMenu(1, price_pan, price_modifier, inventory);
                    break;
                case 3:
                    inventory = buyingItemMenu(2, price_Cauldron, price_modifier, inventory);
                    break;
                case 4:
                    cout << endl;
                    break;
                default:
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                    break;
                }
            } while (input < 1 || input > 4);

            printMenuLine();
            break;

        //Weapons
        case 3:
            do {
                cout << "\nI have a plentiful collection of weapons to choose from, what would you like?" << endl <<
                        "Note that some of them provide you a special bonus in combat, marked by a (+X)." << "\n\n" <<
                        "Choose one of the following:" << endl <<
                        " 1. Stone Club [" << price_club*price_modifier << " Gold]" << endl <<
                        " 2. Iron Spear [" << price_spear*price_modifier << " Gold]" << endl <<
                        " 3. (+1) Mythril Rapier [" << price_rapier*price_modifier << " Gold]" << endl <<
                        " 4. (+2) Flaming Battle-Axe [" << price_ax*price_modifier << " Gold]" << endl <<
                        " 5. (+3) Vorpal Longsword [" << price_sword*price_modifier << " Gold]" << endl <<
                        " 6. Cancel\n\n> ";
                cin >> input_string;
                input = getNum(input_string);
                switch (input) {
                case 1:
                    inventory = buyingItemMenu(3, price_club, price_modifier, inventory);
                    break;
                case 2:
                    inventory = buyingItemMenu(4, price_spear, price_modifier, inventory);
                    break;
                case 3:
                    inventory = buyingItemMenu(5, price_rapier, price_modifier, inventory);
                    break;
                case 4:
                    inventory = buyingItemMenu(6, price_ax, price_modifier, inventory);
                    break;
                case 5:
                    inventory = buyingItemMenu(7, price_sword, price_modifier, inventory);
                    break;
                case 6:
                    cout << endl;
                    break;
                default:
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                    break;
                }
            } while (input < 1 || input > 6);

            printMenuLine();
            break;

        //Armor
        case 4:
            do {
                printf("\nHow many suits of armor can I get you? [%.2f Gold/suit]? (0 to cancel)\n\n> ", price_modifier*price_armor);
                cin >> input_string;
                input = getNum(input_string);
                if (input == 0) {
                    break;
                }
                else if (input > 0) {
                    inventory = wantToPurchase(14, "suit", "of armor", input, price_armor, price_modifier, inventory);
                }
                else {
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                }
            } while (input < 0);

            break;
        //Treasures
        case 5:
            total_sell = getTotalTreasurePrice(price_modifier, inventory);
            if (total_sell <=0) {
                cout << "\nYou have no treasures." << endl;
                break;
            }
            do {
                cout << "\nWould you like to sell all your treasures for "<< total_sell << "? (y/n)\n\n> ";
                cin >> input_string;
                input_char=input_string[0];
                if (toupper(input_char) == 'Y') {
                    inventory.addGold(total_sell);
                    for (int index=8; index<13; index++) {
                        inventory.getItem(index).setItemNum(0);
                    }
                    break;
                }
                else if (toupper(input_char) != 'N') {
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                }
                else {
                    break;
                }
            } while (toupper(input_char != 'Y'));

            printMenuLine();
            break;
        //Leave
        case 6:
            do {
                cout << "\nAre you sure you're finished? You won't be able to buy anything else from me! (y/n)\n\n> ";
                cin >> input_string;
                input_char=input_string[0];
                if (toupper(input_char) == 'Y') {
                    printMenuLine();
                    return inventory;
                }
                else if (toupper(input_char) != 'N') {
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                }
                else {
                    break;
                }
            } while (toupper(input_char) != 'Y');

            printMenuLine();
            break;
        default:
            cout << "\nInvalid Input: " << input_string << "\n\n";
            break;
        }
    } while (input_outer != 6);
    return inventory;
}

/*
Prints out num rooms cleared, keys, anger level, inventory and party
intput: Inventory inventory, vector<Character> party, int party_size, int rooms_cleared, int anger_level
*/
void statusUpdate (Inventory inventory, vector<Character> party, int rooms_cleared, int anger_level) {
    cout << "+-------------+" << endl <<
            "| STATUS      |" << endl <<
            "+-------------+" << endl <<
            "| Rooms Cleared: " << rooms_cleared << " | Keys: " << inventory.getKeys() << " | Anger Level: " << anger_level << endl;
            printInventory(inventory);
            printParty(party);
    cout << "+-------------+" << "\n\n";
}

InvenMap cookingMenu(InvenMap inven_map) {
    int input, input_inner, best_cookware;
    vector<Character> party = inven_map.getParty();
    Inventory inventory = inven_map.getInven();

    do {
        if (inventory.getIngredients() < party.size()) {
            cout << "You dont have enough ingredients. 1 per party member. You have " << party.size() << " party members." << endl;
            break;
        }
        else if (inventory.getItemNum(0) <= 0 && inventory.getItemNum(1) <= 0 && inventory.getItemNum(2) <= 0) {
            cout << "You dont have any cookware." << endl;
            break;
        }
        else {
            do {
                cout << "\nHow many meals would you like to cook? (1 ingredient per party member) (0 to cancel)\n\n> ";
                cin >> input_inner;
                if (input_inner <= 0) {
                    return inven_map;
                }
                else {
                    for (int i=0; i<input_inner; i++) {
                        for (int i=0; i<party.size(); i++) {
                            party.at(i).changeFullness(1);
                            inventory.breakBestCookWare();
                        }
                        inventory.addIngredients(-party.size());
                    }
                    inven_map.updateInvenMap(inven_map.getMap(), inventory, party, inven_map.getMonster());
                    return inven_map;
                }
            } while (input_inner != 0);
        }
    } while (input != 0);
    
    return inven_map; // critical failure return value (should never return this value)
}

InvenMap investigate (InvenMap inven_map, int rooms_cleared) {
    int rand_num = randomNum(100);
    bool fight=false;
    Inventory inventory = inven_map.getInven();
    vector<Character> party = inven_map.getParty();

    cout << "\nYour party looks around for a moment." << endl;

    if (rand_num <= 10) {
        cout << "They found a key!" << endl;
        inventory.addKeys(1);
    }
    else if (rand_num > 10 && rand_num <= 30) {
        cout << "They found treasure!" << endl;
        inventory.addItem(8+rooms_cleared, 1);
    }
    else if (rand_num > 30 && rand_num <=50) {
        inven_map.updateInvenMap(fightMonster(inven_map, rooms_cleared+1));
        fight=true;
    }
    else {
        cout << "They found nothing..." << endl;
    }
    if (!fight) {
        for (int i=0; i<party.size(); i++) {
            int fullnessDrop = randomNum(2)-1;
            if (fullnessDrop == 0) {
                party.at(i).changeFullness(-1);
            }
        }
    }
    printMenuLine();
    inven_map.setInven(inventory);
    return inven_map;
}

/*
Lets the user change the equipped armor and weapon for each party member
input: vector<Character> party, int party_size, Inventory inventory
prints options and loops until player chooses to quit
*/
InvenMap equipmentMenu(InvenMap inven_map) {
    int input, input_outer, input_inner, index;
    string input_string;
    Inventory inventory = inven_map.getInven();
    vector<Character> party = inven_map.getParty();

    do {
        printMenuLine();
        printInventory(inventory);
        printParty(party);
        cout << "+-------------+" << "\n\n" <<
                "Who do you wish to equip? (0 to cancel)" << endl;

        for (int i=0; i<party.size(); i++) {
            cout << " " << i+1 << ". " << party.at(i).getName() << " | Weapon: " << party.at(i).getWeapon() << " | Armor: " << party.at(i).getArmor() << endl; //print party
        }
        cout << "\n> ";
        cin >> input_outer;
        
        if (input_outer >= 1 && input_outer <= party.size()+1) {
            do {
                cout << "\nWhat would you like to equip? (0 to cancel)" << endl <<
                        " 1. Weapons (Club: " << inventory.getItemNum(3) << " | Spear: " << inventory.getItemNum(4) <<
                                  " | Rapier: " << inventory.getItemNum(5) << " | Battle Axe: " << inventory.getItemNum(6) <<
                                  " | Longsword: " << inventory.getItemNum(7) << ")" << endl <<
                        " 2. Armor (" << inventory.getArmor() << ")\n\n> ";
                cin >> input_string;
                input = getNum(input_string);

                switch (input) {
                //Weapons
                case 1:
                    do {
                        cout << "\nWhich weapon? (0 to cancel)" << endl <<
                                " 1. Stone Club (" << inventory.getItemNum(3) << ")" << endl <<
                                " 2. Iron Spear (" << inventory.getItemNum(4) << ")" << endl <<
                                " 3. (+1) Mythril Rapier (" << inventory.getItemNum(5) << ")" << endl <<
                                " 4. (+2) Flaming Battle-Axe (" << inventory.getItemNum(6) << ")" << endl <<
                                " 5. (+3) Vorpal Longsword (" << inventory.getItemNum(7) << ")\n\n>";
                        cin >> input_string;
                        input_inner=getNum(input_string);
                        if (input_inner == 0) {
                            break;
                        }
                        else if (inventory.getItemNum(input_inner+2)>0) {
                            char input_char;

                            if (party.at(input_outer-1).getWeapon() != "Hands") {
                                cout << endl << party.at(input_outer-1).getName() << " already has a weapon equiped. Would you like to replace it? (y/n)\n\n> " << endl;
                                cin >> input_string;
                                input_char = input_string[0];

                                if (toupper(input_char) == 'N') {
                                    break;
                                }
                                else if (toupper(input_char) == 'Y') {
                                    index = inventory.getItemIndex("Weapon", party.at(input_outer-1).getWeapon());
                                    if (inventory.getItemNum(index) > 0) {
                                        inventory.addItem(index, 1);
                                        inventory.addItem(input_inner+2, -1);
                                        party.at(input_outer-1).setWeapon(inventory.getItem(input_inner+2).getItemName());
                                        cout << endl << party.at(input_outer-1).getName() << " has equiped " << party.at(input_outer-1).getWeapon() << endl;
                                        break;
                                    }
                                    else {
                                        cout << "\nYou dont have enough of that weapon." << endl;
                                        break;
                                    }
                                }
                                else {
                                    cout << "\nInvalid Input: " << input_string << "\n\n";
                                }
                            }
                            else {
                                inventory.addItem(input_inner+2, -1);
                                party.at(input_outer-1).setWeapon(inventory.getItem(input_inner+2).getItemName());
                                cout << endl << party.at(input_outer-1).getWeapon() << " equiped on " << party.at(input_outer-1).getName() << "\n";
                                break;
                            }
                        }
                        else if (inventory.getItemNum(index) <= 0) {
                            cout << "\nYou dont have enough of that weapon." << endl;
                            break;
                        }
                        else {
                            cout << "\nInvalid Input: " << input_string << "\n\n";
                        }
                    } while (input_inner < 1 || input_inner > 6);

                    break;
                //Armor
                case 2:
                    if (inventory.getArmor()>0) {
                        if (party.at(input_outer-1).getArmor() == true) {
                            cout << party.at(input_outer-1).getName() << " already has armor equiped." << endl;
                            break;
                        }
                        else {
                            inventory.addArmor(-1);
                            party.at(input_outer-1).setArmor(true);
                            cout << "\nArmor equiped on " << party.at(input_outer-1).getName() << endl;
                            break;
                        }
                    }
                    else {
                        cout << "You dont have enough armor." << endl;
                        break;
                    }
                    break;
                case 0:
                    cout << endl;
                    break;
                default:
                    break;
                }
            } while (input != 0);
        }
        else if (input_outer != 0) {
            cout << "\nInvalid Input: " << input_string << "\n\n";
        }
    } while (input_outer != 0);

    inven_map.setInven(inventory);
    inven_map.setParty(party);

    return inven_map;
}

InvenMap actionMenu(InvenMap inven_map, int rooms_cleared, int anger_level, vector<Monster> monster) { 
    int input, player_pos[2];
    char input_char;
    bool move=false;
    string input_string;
    Map map = inven_map.getMap();

    do {
        statusUpdate(inven_map.getInven(), inven_map.getParty(), rooms_cleared, anger_level);
        inven_map.getMap().displayMap();
        cout << "\n\n";
        cout << "Choose an Action:" << endl <<
                " 1. Move" << endl <<
                " 2. Investigate" << endl <<
                " 3. Pick a Fight" << endl <<
                " 4. Cook" << endl <<
                " 5. Equip" << endl <<
                " 6. Tips" << endl <<
                " 7. Give Up\n\n> ";
        cin >> input_string;
        input = getNum(input_string);

        switch (input) {
        case 1: //move
            do {
                cout << "Choose a direction (WASD)." << endl <<
                        "Or type 0 to cancel\n\n> ";
                cin >> input_string;
                input_char=input_string[0];
                
                if (toupper(input_char)!='W' && toupper(input_char)!='A' && toupper(input_char)!='S' && toupper(input_char)!='D' && toupper(input_char)!='0') {
                    cout << "\nInvalid Input: " << input_string << "\n\n";
                }
                else if (input_char == '0') {
                    move=false;
                    break;
                }
                else {
                    map.move(input_char, player_pos);
                    if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && inven_map.getInven().getKeys() > 0) {
                        inven_map.setMap(map);
                        //enter room and doo room things
                    }
                    break;
                }
                move=true;
            } while (input_char != '0');
            inven_map.setMap(map);
            break;
        case 2: //investigate
            if (!inven_map.getMap().isExplored(inven_map.getMap().getPlayerRow(), inven_map.getMap().getPlayerCol())) {
                inven_map.updateInvenMap(investigate(inven_map, rooms_cleared));
                inven_map.updateInvenMap(misfortune(inven_map));
            }
            else {
                cout << "This tile is already explored." << endl;
            } 
            break;
        case 3: //look for fight
            inven_map.updateInvenMap(fightMonster(inven_map, rooms_cleared+1));
            if (!inven_map.getLife()) {
                return inven_map;
            }
            inven_map.updateInvenMap(misfortune(inven_map));
            break;
        case 4: // cook
            inven_map.updateInvenMap(cookingMenu(inven_map));
            inven_map.updateInvenMap(misfortune(inven_map));
            break;
        case 5://equip
            inven_map.updateInvenMap(equipmentMenu(inven_map));
            inven_map.updateInvenMap(misfortune(inven_map));
            break;
        case 6: //tips
            cout << "\nThere are 4 types of spaces on the map." << endl <<
                " 1. Normal spaces: These are the most common type of space and are marked with a '-'." << endl << 
                "    See Normal Space Actions for more details on what the player can do on normal spaces." << endl <<
                "    If the player chooses to take the Investigate action, then the space will be marked as 'explored';" << endl <<
                "    by changing its character to a space ' '." << endl <<
                " 2. Room spaces: These spaces are marked with an 'R' and represent rooms on the map. See Room Space Actions for more details." << endl <<
                "    After the room has been 'cleared', that is, the party has entered the room and defeated the monster inside, the space will" << endl << 
                "    be turned into a normal space and marked as 'explored; by changing its character to a space ' '." << endl <<
                " 3. NPC spaces: These spaces are marked with an 'N' and represent non-player characters that the party can interact with." << endl <<
                "    See NPC Space Actions for more details. These spaces are hidden by default, so they will be displayed on the map as a '-'" << endl <<
                "    until the player moves onto their space. Moving off of the NPC space will leave it revealed as a 'N'. The player can choose" << endl <<
                "    to interact with the NPC. After the player interacts with the NPC, the NPC will leave. This means the space will be changed" << endl <<
                "    to a normal space and marked as 'explored' by changing its character to a space ' '." << endl <<
                " 4. Dungeon exit: The final, and least interesting, space type is the dungeon exit, marked with a 'E'. " << endl <<
                "    After clearing all the rooms, the party will have to move to this space to finish the game." << "\n\n";

            cout << "WASD to move when in the move acion" << endl <<
                    "After moving, each party members' fullness level has a 20% chance of dropping by 1" << endl <<
                    "If the space is not currently marked as 'explored' on the map, the player can choose to investigate their surroundings in hopes of finding a key or treasure." << "\n\n";
            break;
        case 7: //give up
            inven_map.setLife(false);
            break;
        default:
            cout << "\nInvalid Input: " << input_string << "\n\n";
            break;
        }
    } while (input != 7);

    return inven_map;
}