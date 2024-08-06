// readLikesDriver.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #5

#include <iostream>
#include <fstream>
#include "User.h"
#include <string>
#include <vector>

using namespace std;

int split(string input, char separator, string arr[], int size) {
    if (input == "") { // failsafe incase empty string is inputed
        return 0;
    }
    
    string temp = "";
    int count = 0;
    for (int i = 0; i < input.length(); i++) { // will go through all of input
        if (input[i] != separator) { // will add each letter that isn't the delimiter to temp 
            temp += input[i]; 
        } 
        else { // when a delimiter is finally reached in the string
            arr[count] = temp; // will set the array to all the letters before delimiter and reset string temp
            temp = "";
            count++;
            if (count >= size) { // failsafe
                return -1;
            }
        }
    }

    // in a normal input, the final string won't be added into the array since the for loop above will only assign after it reaches a delimiter
    arr[count] = temp; // assigns the last set of strings to the final array with proper index
    count++;
    return count; // returns count
}

int readLikes(string filename, User users[], int numUsersStored, int usersArrSize, int maxPosts) {
    // initialize variables
    string line;
    int length = 0;
    ifstream fin;
    
    if(numUsersStored == usersArrSize) { // failsafe for if there is no more space
        return -2;
    }

    fin.open(filename);

    if (fin.fail()) { // failsafe for if file cannot be opened
        return -1;
    }
    else {
        vector<string> info(maxPosts + 1, "");
        vector<int> likes(maxPosts, -1);
        // the code works normally without this weird vector stuff in coderunner, but refused to work properly in vscode
        // I looked up a solution to this problem and this vector thing came up, I'll be completely honest I don't understand it but I just used it so that problem 8 of pt1 could work

        while (!fin.eof() && numUsersStored < usersArrSize) { // check to see if size is greater than users 
            getline(fin, line);
            int numPosts = 0; // initialize variable to keep track of actual number of posts
            if(line != "") { // check to see if line in file is empty string
                split(line, '|', &info[0], maxPosts + 1); // calls split on the line with proper delimiter
                for (int i = 1; i <= maxPosts && info[i] != ""; i++) {
                    likes[i-1] = stoi(info[i]); // sets correct index of likes to correct value of info
                    numPosts++; // increment number of posts
                }
                
                User u(info[0], &likes[0], numPosts); // sets up variable of User class with info gathered from each line of
                users[numUsersStored] = u; // for every increment of numUseresStored set user[] array to u
                numUsersStored++; // increments return value for next pass of while loop
            }
        }
        fin.close();
        return numUsersStored;
    }
}

int main() {
    User users[3];
    int likes1[3] = {1, 3, 0};
    User u1 = User("bookworm43", likes1, 3);
    users[0] = u1; // insert first object at index 0
    int num_users_stored = 1;
    int users_arr_size = 3;
    int max_posts = 3;
    readLikes("users.txt", users, num_users_stored, users_arr_size, max_posts);
    
    return 0;
}