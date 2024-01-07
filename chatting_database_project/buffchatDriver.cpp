// buffchatDriver.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 2 - Problem #0

#include <iostream>
#include <string>
#include <fstream>
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

void findTagUser(string usernameTag, User users[], int numUsersStored) {    
    int count = 0;
    string username = "";
    string* userNameMatches = new string[numUsersStored]; // dynamically allocate memory for the array
    // not the same as in coderunner, the code in findTagUserDriver.cpp works in coderunner but not in vscode, I again had to look up a solution that I don't understand for the full driver to work
    
    if(numUsersStored <= 0) { // failsade if numUsersStored is negative or 0
        cout << "No users are stored in the database" << endl;
    }
    else {
        for(int i = 0; i < numUsersStored; i++) { // for loop to iterate through each index of users
            username = users[i].getUsername();
            if (username.find(usernameTag) != std::string::npos) { // the find() method returns std::string::npos if the proper string isn't found --> that's why != is there in the argument
                // checks to see if usernameTag is found in the username string
                userNameMatches[count] = username; // if username with tag is found, set value to userNameMatches[]
                count++; // increments count
            }
        }

        if (count > 0) { // checks to see if above for loop was iterated at all --> if there are any usernames with correct tags
            cout << "Here are all the usernames that contain " << usernameTag << endl;
            for(int i = 0; i < count; i++){
                cout << userNameMatches[i] << endl; // prints out all the indexes that contain the correct tags
            }
        }
        else {
            cout << "No matching user found" << endl;
        }
    } 
}

int main() {
    int x = 0; // initializing variables  
    string filename, year;
    int numPostsStored = 0, numUsersStored = 0;
    bool validity = 0; // false
    Post posts[50];
    User users[50];
    string line;
    ifstream fin;

    while (x != 6) {
        // initial print statement, will loop everytime unless user inputs a 4 (code will run once if 6 is entered but will stop)
        cout << "======Main Menu======" << endl << "1. Read Posts" << endl << "2. Print Posts By Year" << endl << "3. Read Likes" << endl << "4. Get Likes" << endl << "5. Find users with matching tag" << endl << "6. Quit" << endl;
        cin >> x;

        if (fin.fail()) { // failsafe for if file cannot be opened
            cout << "File failed to open. No posts saved to database." << endl;
            continue;
        }
        else {
            if (x == 1) {
                cout << "Enter a post file name:" << endl;
                cin >> filename;

                int readPost = readPosts(filename, posts, numPostsStored, 50);
                
                cout << "Here is the variable readPost: " << readPost << endl;

                if (validity) {
                    cout << "Database is full. Some posts may have not been added." << endl;
                }
                else if (readPost == -1) {
                    cout << "File failed to open. No posts saved to the database." << endl;
                    continue;
                }
                else if (readPost == -2) {
                    cout << "Database is already full. No posts were added." << endl;
                    numPostsStored = 50;
                    validity = 1; // true
                    continue;
                }
                else {
                    cout << "Total posts in the database: " << readPost << endl;                    
                    numPostsStored = readPost;
                }
            }
            else if (x == 2) {
                cout << "Enter the year(YY):" << endl;
                cin >> year;
                printPostsByYear(posts, year, numPostsStored);
            }
            else if (x == 3) {
                cout << "Enter a user file name:" << endl;
                cin >> filename;
                int readLike = readLikes(filename, users, numUsersStored, 50, 3);

                if (readLike == -1) {
                    cout << "File failed to open. No users saved to the database." << endl;                    
                }
                else if (readLike == -2) {
                    cout << "Database is already full. No users were added." << endl;
                }
                else if (readLike == 50) {
                    cout << "Database is full. Some users may have not been added." << endl;
                    numUsersStored = 50;
                }
                else if (readLike >= 0 && readLike < 50) {
                    numUsersStored = readLike;
                    cout << "Total users in the database: " << numUsersStored << endl;
                }
            }
            else if (x == 4) {
                string author;
                cout << "Enter a post author: " << endl;
                cin >> author;
                
                string username;
                cout << "Enter a user name: " << endl;
                cin >> username;
                
                int getLike = getLikes(author, posts, numPostsStored, username, users, numUsersStored);
                cout << "Test for variable getLike: " << getLike << endl;

                if (getLike == 0) {
                    cout << username << " has not liked the post posted by " << author << endl;
                }
                else if (getLike == -1) {
                    cout << username << " has not viewed the post posted by " << author << endl;
                }
                else if (getLike == -2) {
                    cout << "Database is empty." << endl;
                }
                else if (getLike == -3) {
                    cout << username << " or " << author << " does not exist." << endl;
                }
                else {
                    cout << username << " liked the post posted by " << author << " " << getLike << " times" << endl;
                }
            }
            else if (x == 5) {
                string tag;
                cout << "Enter a tag: " << endl;
                cin >> tag;
                
                findTagUser(tag, users, numUsersStored);
            }
            else if (x == 6) {
                cout << "Good bye!" << endl;
                return 0;
            }
            else { // failsafe incase invalid input is entered
                cout << "Invalid input." << endl;
            }
        }
    }

    return 0;
}