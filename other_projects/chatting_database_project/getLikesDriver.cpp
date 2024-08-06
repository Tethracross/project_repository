// getLikesDriver.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 1 - Problem #6

#include <iostream>
#include "post.h"
#include "User.h"
#include <iomanip>
using namespace std;

int getLikes(string postAuthor, Post post[], int numPostsStored, string username, User users[], int numUsersStored) { 
   if(numUsersStored <= 0 || numPostsStored <= 0) { // failsafe for if numUsersStored or numPostsStored <= 0
       return -2;
   }
                 
   for(int i = 0; i < numPostsStored; i++) {
       if (post[i].getPostAuthor() == postAuthor) { // if-statement for if the post class getter returns the same as user input
           for(int j = 0; j < numUsersStored; j++) { // for loop iterates as long as j is less than user input for numUsersStored
               if(users[j].getUsername() == username) { // if-statement for if getter for user class is the same as user input for numUsersStored
                   return users[j].getLikesAt(i); // will return 1 or 0 for true/false of the getter for likes
               }
           }
           
       }
   } 
    return -3; // failsafe for if the above nested for-if loop is completely parsed through --> returns -3
}

int main(){
    //Creating 3 posts 
    Post posts[3]; 
    Post my_post_1 = Post("Hello!","Xuefei", 10, "10/02/22");
    posts[0] = my_post_1;
    Post my_post_2 = Post("new post","Morgan", 9, "10/04/22");
    posts[1] = my_post_2;
    Post my_post_3 = Post("Hey!","Jot", 10, "10/05/22");
    posts[2] = my_post_3;

    //Printing values in each post object 
    cout << "Posts: " << endl;        
    cout << posts[0].getPostAuthor() << " posted " << posts[0].getPostBody() << " on " << posts[0].getPostDate() << endl; 
    cout << posts[1].getPostAuthor() << " posted " << posts[1].getPostBody() << " on " << posts[1].getPostDate() << endl; 
    cout << posts[2].getPostAuthor() << " posted " << posts[2].getPostBody() << " on " << posts[2].getPostDate() << endl; 

    //Creating 2 users 
    User users[2];
    // user 1
    int likes1[3] = {1, 3, 2};
    User u1 = User("bookworm43", likes1, 3);
    users[0] = u1; // insert first object at index 0
    // user 2
    users[1].setUsername("roboticscu");
    users[1].setLikesAt(0,-1); 
    users[1].setLikesAt(1,2); 
    users[1].setLikesAt(2,4);

    //Values in each user object 
    cout<<"Users and posts they liked: "<<endl; 
    cout<<users[0].getUsername()<<": "<<users[0].getLikesAt(0)<<", "<<users[0].getLikesAt(1)<<", "<<users[0].getLikesAt(2)<<endl;
    cout<<users[1].getUsername()<<": "<<users[1].getLikesAt(0)<<", "<<users[1].getLikesAt(1)<<", "<<users[1].getLikesAt(2)<<endl;

    getLikes("Xuefei", posts, 3, "bookworm43", users, 2);

    getLikes("Morgan", posts, 3, "cubikingclub", users, 2);

    getLikes("Raegan", posts, 3, "bookworm43", users, 2);

    User user_array[50];
    getLikes("Raegan", posts, 3, "cubikingclub", users, 0);
    getLikes("Raegan", posts, 3, "bookworm43", user_array, 0);
}