// project2pt2.cpp
// CSCI 1300 Spring 2023
// Author: Vishnu Duriseti
// Recitation: 101 - Ojasvi Bhalerao
// Project 2 pt. 2

#include <iostream>
#include "Post.h"
#include "User.h"
#include <fstream>
#include <string>
#include <vector>

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

    Buffchat::Buffchat() {
        numPosts = 0;
        numUsers = 0;
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

                    if (validity) { // if the whole array is a valid input
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

                    for (int i = 1; i <= maxPosts; i++) { 
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

        int min = 9999999 /*super high number*/, countPosts = 0, minIndex = 0; 

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

    int main() {
        int x = 0; // initializing variables  
        string filename, year;
        int numPostsStored = 0, numUsersStored = 0, value;
        bool validity = 0; // false
        Post posts[50];
        User users[50];
        Buffchat b;

        while (x != 10) {
            // initial print statement, will loop everytime unless user inputs a 4 (code will run once if 6 is entered but will stop)
            cout << "======Main Menu=====" << endl << "1. Read posts" << endl << "2. Print Posts By Year" << endl << "3. Read Likes" << endl << "4. Get Likes" << endl << "5. Find users with matching tag" << endl << "6. Add a new post" << endl << "7. Print popular posts for a year" << endl << "8. Find least active user" << endl << "9. Find unique likes for a post author" << endl << "10. Quit" << endl;
            cin >> x;
            if (x == 1) {
                cout << "Enter a post file name:" << endl;
                cin >> filename;

                value = b.readPosts(filename);
                if (validity) {
                    cout << "Database is already full. No posts were added." << endl;
                }
                else if(value == -2) {
                    cout << "Database is full. Some posts may have not been added." << endl;
                    numPostsStored = 50;
                    validity = true;
                    continue;
                } 
                else if (value == -1) {
                    cout << "File failed to open. No posts saved to the database." << endl;
                    continue;
                } 
                else {
                numPostsStored = value;
                cout << "Total posts in the database: " << value << endl;
                    
                }
            }
            else if (x == 2) {
                cout << "Enter the year(YY):" << endl;
                cin >> year;
                b.printPostsByYear(year);
            }
            else if (x == 3) {
                cout << "Enter a user file name:" << endl;
                cin >> filename;
                value = b.readLikes(filename);

                if(value == -1) {
                    cout << "File failed to open. No users saved to the database." << endl;
                }
                else if(value == -2) {
                    cout << "Database is already full. No users were added." << endl;
                }
                else if(value == 50) {
                    cout << "Database is full. Some users may have not been added." << endl;
                    numUsersStored = 50;
                }
                else if(value >= 0 && value < 50) {
                    numUsersStored = value;
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

                value = b.getLikes(author, username);
                    
                if(value == 0) {
                    cout << username << " has not liked the post posted by " << author<< endl;
                }
                else if(value == -1) {
                    cout << username << " has not viewed the post posted by " << author << endl;
                }
                else if(value == -2) {
                    cout << "Database is empty." << endl;
                }
                else if(value == -3) {
                    cout << username << " or " << author << " does not exist." << endl;
                }
                else {
                    cout << username << " liked the post posted by " << author << " " << value << " times" << endl;
                }
            }
                else if (x == 5) {
                    string tag;
                    cout << "Enter a tag: " << endl;
                    cin >> tag;
                    
                    b.findTagUser(tag);
                }
                else if (x == 6) {
                string body, author, date;
                cout << "Enter a post body:" << endl;
                cin >> body;
                cout << "Enter a post author:" << endl;
                cin >> author;
                cout << "Enter a date(mm/dd/yy):" << endl;
                cin >> date;
                
                if (b.addPost(body, author, date)) {
                    cout << author << "'s post added successfully" << endl;
                } 
                else {
                    cout << "Database is already full. " << author << "'s post was not added" << endl;
                }
                
                } 
                else if (x == 7) {
                    int count;
                    string year;
                    cout << "Enter the minimum number of likes for posts:" << endl;
                    cin >> count;
                    cout << "Enter the year(YY):" << endl;
                    cin >> year;
                    b.printPopularPosts(count, year);
                } 
                else if (x == 8) {
                    if (b.getUserSize() <= 0 || b.findLeastActiveUser().getUsername() == "") {
                    cout << "There are no users stored" << endl;
                    } 
                    else {
                    cout << b.findLeastActiveUser().getUsername() << " is the least active user"<< endl;
                    }
                } 
                else if (x == 9) {
                    string author;
                    cout << "Enter a post author:" << endl;
                    cin >> author;
                    cout << "The posts posted by " << author << " have been liked by " << b.countUniqueLikes(author) << " unique users." << endl;
                }
                else if (x == 10) {
                    cout << "Good bye!" << endl;
                    return 0;
                }
                else { // failsafe incase invalid input is entered
                    cout << "Invalid input" << endl;
                }
            }
        return 0;
    }