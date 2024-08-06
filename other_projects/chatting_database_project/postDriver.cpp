#include <iostream>
#include <iomanip>
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