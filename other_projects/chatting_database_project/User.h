// User.h
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #4

#include <iostream>
using namespace std;

class User {
    
    private:
        string username;
        int likes[50];
        int numPosts;
        static const int size = 50;

    public:
        User();
        User(string name, int arr[10], int num);

        string getUsername();
        int getLikesAt(int postID);
        int getNumPosts();
        int getSize();

        void setUsername(string username_);
        bool setLikesAt(int postID, int numLikes);
        void setNumPosts(int posts);
};