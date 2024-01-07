// Post.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #1

#include <iostream>
#include "Post.h"
using namespace std;

Post::Post() {
    body = "";
    postAuthor = ""; 
    numLikes = 0;
    date = "";
}

Post::Post(string body_, string post_author_, int num_likes_, string date_) {
    body = body_;
    postAuthor = post_author_;
    numLikes = num_likes_;
    date = date_;
}

string Post::getPostBody() {
    return body;
}

string Post::getPostAuthor() {  
    return postAuthor;
}

int Post::getPostLikes() {
    return numLikes;
}

string Post::getPostDate() {
    return date;
}

void Post::setPostBody(string s) {
    body = s;
}

void Post::setPostAuthor(string s) {
    postAuthor = s;
}

void Post::setPostLikes(int i) {
    if (i >= 0) {
        numLikes = i;
    }
}

void Post::setPostDate(string s) {
    date = s;
}

