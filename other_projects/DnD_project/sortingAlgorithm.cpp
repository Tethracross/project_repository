// CSCI 1300 Spring 2023
// Author: Michael Chapp, Vishnu Duriseti
// Project 3 Sorting algorithm

#include <iostream>
#include <vector>

using namespace std;

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp; // declare variables for the algorithm

    for (i = 0; i < n-1; i++) { // loop through the array
        minIndex = i; // set the current index as the minimum

        for (j = i+1; j < n; j++) { // loop through the rest of the array to find the smallest value
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // set minIndex to index of array with the next smallest value
            }
        }

        if (minIndex != i) { // if the minimum is not at the current index, swap the values
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int main() {
    int arr[] = {100, 10, 32, 356, 982, 90, 1, 76, 43, 67, 3}; // initialize an array
    int n = 11;
    
    selectionSort(arr, n); // sort the array
    cout << "Sorted array: "; // output the sorted array
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
    return 0;
}

