// readPostsDriver.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #2

#include <iostream>
#include "Post.h"
#include <fstream>
#include <cassert>
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

int readPosts(string filename, Post posts[], int numPostsStored, int postsArrSize) {
    if(numPostsStored == postsArrSize) { //Setting parameters while checking if posts equal to your posts size
        return -2;
    } 
    
    string line; // variable for storing each line as we read it
    ifstream fin; // file input stream
    bool validity = true;

    fin.open(filename); // Open input file
    
    if (fin.fail()) { // if file fails to open
        return -1;
    }
    else {
        string input[4];
        while (!fin.eof() && numPostsStored < postsArrSize) {
            getline(fin, line);
            if(line != "") {
                split(line, '|', input, 4); // If line isn't empty --> run split function with parameters: {line, info, input[], 4}
                validity = true;
                for (int i=0; i<input[2].length(); i++){
                    if (!isdigit(input[2][i])) {
                        validity = false;
                    }
                    // for loop is constantly looping --> non valid entry will return false
                }
                if (validity) { // Checks for validity of entry and increments number of posts 
                    Post p = Post(input[0], input[1], stoi(input[2]), input[3]);
                    posts[numPostsStored] = p;
                    numPostsStored++;
                }
            }
        }

        fin.close();
        
        return numPostsStored;
    }
}

int main() {
    Post posts[10];
    assert (readPosts("Post.txt", posts, 0, 9) == 3);

    Post posts2[10];
    assert (readPosts("Posttest2.txt", posts, 0, 10) == 4);
}
