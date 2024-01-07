// Post.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #4

#include <iostream>
#include "User.h"
using namespace std;

User::User() {
    username = "";
    numPosts = 0;
    
    for (int i = 0; i < size; i++) {
        likes[i] = -1;
    }
}

User::User(string name, int arr[], int num) {
    if (num < size) {
       for (int i=0; i < num; i++) {
           likes[i] = arr[i]; // will set all indexes of arr[] to likes[] 
       }
       
       for (int i = num; i < size; i++){
           likes[i] = -1; // some indexes of likes[] will be left over --> these indexes will be set to -1
       }
    
   }

   if (num == size) { 
       for (int i=0; i < num; i++){ 
           likes[i] = arr[i]; // will set all values of input variable arr[] to private variable likes[]
       }
   }

   username = name;
   numPosts = num; 
}

string User::getUsername() {
    return username;
}

int User::getLikesAt(int postID) {
    if (postID >= size || postID < 0) {
        return -2;
    }
    else {
        return likes[postID];
    }
}

int User::getNumPosts() {
    return numPosts;
}

int User::getSize() {
    return size;
}


void User::setUsername(string username_) {
    username = username_;
}

bool User::setLikesAt(int postID, int numLikes) {
    if ((postID >= 0 && postID < numPosts) && (numLikes >= -1 && numLikes <= 10)) {
        likes[postID] = numLikes;
        return 1; // true
    }
    else {
        return 0; // false
    }
}

void User::setNumPosts(int posts) {
    if (posts >= 0 && posts <= size) {
        numPosts = posts;
    }
}
