// Buffchat.h
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 2 - Problem #0

#include <iostream>
#include "Post.h"
#include "User.h"
using namespace std;

class Buffchat {

    private:
    static const int postsSize = 50;
    static const int usersSize = 50;
    int numUsers;
    int numPosts;
    Post posts[postsSize];
    User users[usersSize];

    public:
    Buffchat();

    int getPostSize();
    int getUserSize();
    int getNumPosts();
    int getNumUsers();

    int readPosts(string filename);
    void printPostsByYear(string year);
    int readLikes(string filename);
    int getLikes(string postAuthor, string username);
    void findTagUser(string usernameTag);
    bool addPost(string postBody, string postAuthor, string date);
    void printPopularPosts(int count, string year);
    User findLeastActiveUser();
    int countUniqueLikes(string postAuthor);
};
