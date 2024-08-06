// Buffchat.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 2 - Problem #0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    int getLikes(string post_author, string username);
    void findTagUser(string username_tag);
    bool addPost(string post_body, string post_author, string date);
    void printPopularPosts(int count, string year);
    User findLeastActiveUser();
    int countUniqueLikes(string post_author);
};

Buffchat::Buffchat() {
    numPosts = 0;
    numUsers = 0;
}

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

int Buffchat::getPostSize() {
    return postsSize;
}

int Buffchat::getUserSize() {
    return usersSize;
}

int Buffchat::getNumPosts() {
    return numPosts;
}

int Buffchat::getNumUsers() {
    return numUsers;
}

int Buffchat::readPosts(string filename) {
     if(numPosts == 50) { // failsafe for if max is reached
        return -2;
    } 
    
    string line; 
    ifstream fin; 
    bool validity = 1; // true

    fin.open(filename);
    
    if (fin.fail()) {
        return -1;
    }
    else {
        string info[4];
        while (!fin.eof() && numPosts < 50)
        {
            getline(fin, line);
            if(line != "") {
                split(line, '|', info, 4); // calls split function
                validity = true;

                for (int i = 0; i < info[2].length(); i++) {
                    if (!isdigit(info[2][i])) { // check to see if info[2][i] is a valid input
                        validity = 0; // false
                    }
                }

                if (validity) { // if it is a valid input
                    Post p = Post(info[0], info[1], stoi(info[2]), info[3]); // calls post class with correct info in array
                    posts[numPosts] = p;
                    numPosts++; // increments return variable
                }
                //If you do have a valid entry then you will increment your number of posts 
            }
        }

        fin.close();
        
        return numPosts;
    }
}

void Buffchat::printPostsByYear(string year) {
    string postdate = ""; // initialize to holding values
    int count = 0;

    if(numPosts <= 0) { // failsafe for invalid or 0 for entry of numPosts
        cout <<"No posts are stored" << endl;
    }
    else if (numPosts >= 1) { // check to see if numPosts is valid
        for(int i = 0; i < numPosts; i++) {
            postdate = posts[i].getPostDate();
            if (postdate.substr(6, 2) == year) { // check to see if correct year is in place
                if (count == 0) {
                    cout <<"Here is a list of posts for year " << year << endl;
                }
                cout << posts[i].getPostBody() << endl; // prints list of posts
                count++;
            }
        }
        if (count == 0) {
            cout << "No posts stored for year "  << year << endl;
        }
    }
}

int Buffchat::readLikes(string filename) {
    string line;
    int maxPosts = 3;
    ifstream fin;

    int length = 0;
    //Declare your variables 
    
    if(numUsers == 50) {
        return -2;
    }

    fin.open(filename);

    if (fin.fail()) {
        return -1;
    }
    else {
        string info[maxPosts + 1];
        int likes[maxPosts];

        while (!fin.eof() && numUsers < 50)
        {
            getline(fin, line);

            for (int i = 0; i< maxPosts; i++) {
                likes[i] = -1;
            }

            if(line != "") {
                split(line, ',', info, maxPosts + 1); // calls split if line in file is valid

                for (int i = 1; i <= maxPosts; i++) { // 1, 2, 3
                    if (i < maxPosts) {
                        likes[i-1] = stoi(info[i]); // sets proper index of likes to integer in info
                    } 
                }
                
                User u = User(info[0], likes, maxPosts);
                users[numUsers] = u;
                numUsers++; // incrementes return variable
            }
        }
    
        fin.close();
        return numUsers;
    }
}

int Buffchat::getLikes(string postAuthor, string username) {
    if(numUsers <= 0 || numPosts <= 0) { // failsafe for invalid numUser and numPosts
       return -2;
   }
                 
   for(int i = 0; i < numPosts; i++) {
       if (posts[i].getPostAuthor() == postAuthor) { // passes getPostAuthor on every index of i to check validity
           for(int j = 0; j < numUsers; j++) { 
               if(users[j].getUsername() == username) { // pass getPostUser on every index of j to check validity 
                   return users[j].getLikesAt(i);
               }
           }
           
       }
   } 

    return -3; // failsafe incase nested loop doesn't iterate through completely
}

void Buffchat::findTagUser(string usernameTag)
{
    string usernameMatches[numUsers];

    int count = 0; // initialize variables with placeholder values
    string username = "";

    if(numUsers <= 0) { // failsafe for if numUsers <= 0
        cout << "No users are stored in the database" << endl;
    }
    else {
        for(int i = 0; i < numUsers; i++) {
            username = users[i].getUsername();
            if (username.find(usernameTag) != std::string::npos) { // checks to see if we HAVEN'T reached end of username
                usernameMatches[count] = username; // set index of count of usernamtmatches to username
                count++; // increments count
            }
        }

        if (count > 0) { // if above nested for loop iterated through and count got incremented atleast once
            cout << "Here are all the usernames that contain " << usernameTag << endl;
            for(int i = 0; i < count; i++) { // prints all usernames
                cout << usernameMatches[i] << endl;
            }
        }
        else {
            cout << "No matching user found" << endl;
        }
    }
}

bool Buffchat::addPost(string post_body, string post_author, string date) {
    if(numPosts == 50) {
        return 0; // false
    }

    Post p = Post();
    p.setPostDate(date);
    p.setPostAuthor(post_author);
    p.setPostBody(post_body);
    p.setPostLikes(0);
    posts[numPosts] = p;
    for(int i = 0; i < numUsers; i++) // sets to -1 as they haven't viewed it
    {
        users[i].setLikesAt(numPosts, -1);
    }
    numPosts++;
    return 1; // true
}

void Buffchat::printPopularPosts(int minLikes, string year) {
    if (numPosts <= 0) { // failsafe incase numPosts is invalid
        cout << "No posts are stored" << endl;
    }
    
    int numValidPosts = 0;
    bool validity = 0; // year --> initialized as false
    Post returnArr[numPosts];
    
    for (int i = 0; i < numPosts; i++) {
        if (posts[i].getPostDate().substr(6,2) == year) { // check to see if year of posts is same as user input
            validity = true;

            if (posts[i].getPostLikes() >= minLikes) { // check to see if post has more than minimmum # of likes
                numValidPosts++; // increments number of valid posts
                returnArr[numValidPosts] = posts[i]; // sets the valid post in post[] into the return array 
            }
        }
    }

    // all the if statements below
    if (validity == false) {
        cout << "No posts stored for year " << year << endl;
    }
    else if (numValidPosts <= 0) {
        cout << "No posts found for year " << year << " with likes more than " << minLikes << endl;
    }
    else {
        cout << "Top posts for year " << year << " with likes more than " << minLikes << endl;
        for (int i = 0; i < numValidPosts; i++) {
            cout << returnArr[i].getPostLikes() << " likes: " << returnArr[i].getPostBody() << endl;
        }
    }
}

User Buffchat::findLeastActiveUser() {
    if(numUsers <= 0) { // least possible active user
        return User();
    }

    int min = 9999999 /*super high number*/, int countPosts = 0, int minIndex = 0; 

    for(int i = 0; i < numUsers ; i++) {
        for(int j = 0; j < users[i].getNumPosts(); j++) { // adds up number of posts viewe
            if(users[i].getLikesAt(j) == -1) { // if getLikesAt returns a failsafe value then increment countPosts
                countPosts++;
            }
        }

        if(min < countPosts) {  // as long as countPosts is less than min set temp to users with proper index and min to countposts
            minIndex = i; // sets index of return array to lowest user
        }
    }

    return users[minIndex];
}

int Buffchat::countUniqueLikes(string postAuthor) {
    if(numPosts <= 0 || numUsers <= 0) { // if either are 0 or less than --> return -2
        return -2;
    }

    bool viewed = 0; // false
    int likes = 0;

    for(int i = 0; i < numPosts; i++) { // nested for loop increments to see if numPosts is greater
        if(posts[i].getPostAuthor() == postAuthor) {
            for (int j = 0; j < numUsers; j++) {
                if (users[j].getLikesAt(i) >= 0) {
                    viewed = 1;
                }
                if (users[j].getLikesAt(i) > 0) {
                    likes++;
                }
            }
        }
    }

    if(viewed == false) { // if holder is false
        return -1;
    }

    return likes; // return variable
}