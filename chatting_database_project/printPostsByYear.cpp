// printPostsByYear.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #3

#include <iostream>
#include <string.h>

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

void printPostsByYear(Post posts[], string year, int numPostsStored) { 
    //Set your variables equal to empty string or 0
    string postdate = "";
    int count = 0;

    if(numPostsStored <= 0) { // failsafe for if numPostsStored <= 0
        cout << "No posts are stored" << endl;
    } 
    else if (numPostsStored >= 1){
        for(int i = 0; i < numPostsStored; i++) { // increments for all indexes of posts[] with values
            postdate = posts[i].getPostDate();
            if (postdate.substr(6, 2) == year) {  // will check every index of posts to see if year matches input year
                if (count == 0) { // will only print line below once if atleast one post with correct year is found
                    cout << "Here is a list of posts for year " << year << endl;
                }
                cout << posts[i].getPostBody() << endl;
                count++;
            }
            
        }
        if (count == 0) { // failsafe if count is not incremented
            cout << "No posts stored for year "  << year << endl;
        }
    } 
}

int main() {
    // two posts that are posted in year 22.
    Post p_1 = Post("new post1","Lisa1", 10, "10/02/22");
    Post p_2 = Post("new post2","Lisa2", 11, "10/02/22");
    Post p_3 = Post("new post3","Lisa3", 8, "10/02/19");

    Post list_of_posts[] = {p_1, p_2, p_3};
    int number_of_posts = 3;
    string year = "22";
    printPostsByYear(list_of_posts, year, number_of_posts);
}
