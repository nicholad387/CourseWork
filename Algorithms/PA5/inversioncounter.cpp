/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      :  Nicholas Mohamed
 * Version     : 1.0
 * Date        : November 1, 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long cnt = 0;
    
    for (int i = 0; i < length; i++) {
        for (int j = i + 1 ; j < length; j++) {
            if (array[j] < array[i]) {
                cnt ++;
            }
        }
    }
    return cnt;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    long num_inversions = 0;
    
    num_inversions = mergesort(array, &scratch[0], 0, length - 1);
    delete [] scratch;
    
    return num_inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long inversion_cnt = 0;
    
    if (low < high) {
        int mid = low + (high - low) / 2;
        
        inversion_cnt = mergesort(array, scratch, low, mid);
        inversion_cnt = inversion_cnt + mergesort(array, scratch, mid + 1, high);
        
        int subLow = low; 
        int subHigh = mid + 1; 
        
        for (int i = low; i <= high; i++) {
            if ((subLow <= mid) && ((subHigh > high) || array[subLow] <= array[subHigh])) {
                scratch[i] = array[subLow];
                subLow++;
            } else {
                scratch[i] = array[subHigh];
                inversion_cnt = inversion_cnt + (mid - subLow + 1);
                subHigh++;
            }
        }
        
        for (int i = low; i <= high; i++) {     // rebiuld array 
            array[i] = scratch[i];
        }
    
    }

    return inversion_cnt;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    
    if (argc > 2) {     // check if more arguments then allowed
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    } else if (argc == 2){
        if (strcmp(argv[1], "slow") != 0){  //from google to check if the arument says slow 
            cerr << "Error: Unrecognized option '"<< argv[1] << "'." << endl;
            return 1;
        }
    }
        

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if (values.size() == 0) {  // throw error, nothing was inputted 
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    
    if (argc == 1) {    // no command line to run slow 
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size());
    } else {    // command line argument to run slow
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size());
    }

    return 0;
}
