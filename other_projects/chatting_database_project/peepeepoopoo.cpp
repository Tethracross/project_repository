


int main(){
    //In your main function you will then reference your strings and your variable types
    //You will then reference Post posts[50] and your value and choice 
    string filename, year, targetTune;
    int num_posts_stored = 0;
    int num_users_stored = 0;
    bool check = false;
    Post posts[50];
    User users[50];
    int value = 0;
    string choice;
    while (choice != "6") //six is exit case, while loop keeps running until that's hit
    {
        cout << "======Main Menu======\n1. Read Posts"
        << "\n2. Print Posts By Year"
        << "\n3. Read Likes"
        << "\n4. Get Likes"
        << "\n5. Find users with matching tag"
        << "\n6. Quit" << endl;
        cin >> choice;
        if(choice == "1") {
            cout << "Enter a post file name:" << endl;
            cin >> filename;
            value = readPosts(filename, posts, num_posts_stored, 50);
            if(check)
            {
                cout << "Database is already full. No posts were added." << endl;
            }
            else if(value == -2) {
                cout << "Database is full. Some posts may have not been added." << endl;
                num_posts_stored = 50;
                check = true;
                continue;
            } else if(value == -1){
                cout << "File failed to open. No posts saved to the database." << endl;
                continue;
            } else {
            num_posts_stored = value;
            cout << "Total posts in the database: " << value << endl;
                
            }
            //Here when your choice is 1 you will then reference your readpost functions 
            //You will then reference your number of post stored and then see if the value is equal to -1 and -2 and then print out if you file is able to be opened
        } else if(choice == "2") {
            cout << "Enter the year(YY):" << endl;
            cin >> year;
            printPostsByYear(posts, year, num_posts_stored);
        } else if(choice == "3") {
            cout << "Enter a user file name:" << endl;
            cin >> filename;
            // value = readLikes(filename, users, num_users_stored, 50, num_posts_stored);
            value = readLikes(filename, users, num_users_stored, 50, 3);
            if(value == -1)
            {
                cout << "File failed to open. No users saved to the database." << endl;
            }
            else if(value == -2)
            {
                cout << "Database is already full. No users were added." << endl;
            }
            else if(value == 50)
            {
                cout << "Database is full. Some users may have not been added." << endl;
                num_users_stored = 50;
            }
            else if(value >= 0 && value < 50)
            {
                num_users_stored = value;
                cout << "Total users in the database: " << num_users_stored << endl;
            }
            //In this one if your choice is equal to 2 you will reference your readLikes function with all of your parameters
            //You will then run it through if else statements and then see if your print out if your database is full 
        } else if(choice == "4") {
            string author;
            cout << "Enter a post author:" << endl;
            cin >> author;
            string username;
            cout << "Enter a user name:" << endl;
            cin >> username;
            value = getLikes(author, posts, num_posts_stored, username, users, num_users_stored);
            if(value == 0)
            {
                cout << username << " has not liked the post posted by " << author<< endl;
            }
            else if(value == -1)
            {
                cout << username << " has not viewed the post posted by " << author << endl;
            }
            else if(value == -2)
            {
                cout << "Database is empty." << endl;
            }
            else if(value == -3)
            {
                cout << username << " or " << author << " does not exist." << endl;
            }
            else
            {
                cout << username << " liked the post posted by " << author << " " << value << " times" << endl;
            }
            //Here you if choice 4 is selected you will then reference your getLikes and then print out your values and then print out if a username hasn't liked the post
            //In your else if you will then check to see if your database is empty and then if not print out the author
        } else if(choice == "5") {
            string tag;
            cout << "Enter a tag: " << endl;
            cin >> tag;
            findTagUser(tag, users, num_users_stored);

//In your else if you will pick choice 5 and then reference your findtaguser and then enter a tag and reference your tag, user, number of users stored
//If choice 6 is picked then you will print out goodbye
        } else if(choice == "6") {
            cout << "Good bye!" << endl;
        } else {
            cout << "Invalid input." << endl;
        }
    }
}