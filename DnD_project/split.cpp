#include <iostream>
using namespace std;

int split(string input_string, char separator, string arr[], int arr_size) {
    int section=0, last_break=0;
    
    //validation
    if (input_string.length() == 0) {
        return 0;
    }

    for (int i=0; i<input_string.length(); i++) {

        //finding each break point
        if (input_string[i] == separator) {
            section++;
            last_break = i+1;
        }

        //make sure you stay in rang of array
        if (section+1 > arr_size) {
            return -1;
        }

        //saving each section in array
        arr[section] = input_string.substr(last_break, i-last_break+1);
    }
    return section+1;
}