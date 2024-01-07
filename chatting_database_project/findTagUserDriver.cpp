// findTagUserDriver.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #7

#include <iostream>
#include "User.h"
using namespace std;

void findTagUser(string usernameTag, User users[], int numUsersStored) {    
    string userNameMatches[numUsersStored];
    int count = 0;
    string username = "";
    
    if(numUsersStored <= 0) { // failsade if numUsersStored is negative or 0
        cout << "No users are stored in the database" << endl;
    }
    else {
        for(int i = 0; i < numUsersStored; i++) { // for loop to iterate through each index of users
            username = users[i].getUsername();
            if (username.find(usernameTag) != std::string::npos) { // the find() method returns std::string::npos if the proper string isn't found --> that's why != is there in the argument
                // checks to see if usernameTag is found in the username string
                userNameMatches[count] = username; // if username with tag is found, set value to userNameMatches[]
                count++; // increments count
            }
        }

        if (count > 0) { // checks to see if above for loop was iterated at all --> if there are any usernames with correct tags
            cout << "Here are all the usernames that contain " << usernameTag << endl;
            for(int i = 0; i < count; i++){
                cout << userNameMatches[i] << endl; // prints out all the indexes that contain the correct tags
            }
        }
        else {
            cout << "No matching user found" << endl;
        }
    } 
}

int main(){
    // creating 5 users
    User user_array[5];
    int likes1[3] = {1, 0, -1};
    int likes2[3] = {4, 5, 0};
    user_array[0] = User("foliwn22", likes1, 3);
    user_array[1] = User("joh23k", likes2, 3);
    user_array[2] = User("harry02", likes2, 3);
    user_array[3] = User("luwkml1", likes2, 3);
    user_array[4] = User("fwollow3", likes1, 3);
    findTagUser("wkm", user_array, 5);

    findTagUser("ou", user_array, 5);

    findTagUser("ol", user_array, 5);

    findTagUser("ol", user_array, 5);
}
