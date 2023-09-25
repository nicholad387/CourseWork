/*******************************************************************************
 * Name        : unique.cpp
 * Author      : 
 * Date        : September 28, 2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (const auto &letter: s){
        if (!(islower(letter))){ // islower method is prebuilt method 
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
    unsigned int check = 0;
    unsigned int set;
    for (const auto &letter: s){
        set = 1 << (letter - 'a'); // finds the binary of the letter
        if ((check & set) == 0){
            check = (check | set);
        }else{
            return false;
        }
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    
    if (argc != 2){
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }
    if (!(is_all_lowercase(argv[1]))){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    if (all_unique_letters(argv[1])){
        cout << "All letters are unique." << endl;
    }else{
        cout << "Duplicate letters found." << endl;
    }
    
    return 0;
}
