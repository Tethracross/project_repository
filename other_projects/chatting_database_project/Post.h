// Post.h
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #1

#include <iostream>
using namespace std;

class Post {

private:
    string body;
    string postAuthor;
    int numLikes;
    string date;

public:
    Post();
    Post(string body_, string post_author_, int num_likes_, string date_);

    string getPostBody();
    string getPostAuthor();
    int getPostLikes();
    string getPostDate();

    void setPostBody(string postBody);
    void setPostAuthor(string author);
    void setPostLikes(int likes);
    void setPostDate(string postDate);
};
