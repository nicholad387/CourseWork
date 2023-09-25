/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : 
 * Date        : October 2, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int> > num_ways;
    vector<vector<int> > result;
    if (num_stairs <= 0){
        num_ways.push_back(vector<int>());
    }else{
        for (int i = 1; i < 4; i++){        // go through each type of move 
            if (num_stairs >= i){        //check if its possible to move by i steps 
                result = get_ways(num_stairs - i);      // go back and do it again after making a move 
                for (auto it = result.begin(); it != result.end(); ++it){ 
                    it -> insert(it -> begin(), i);     // add i to the answer
                }
                num_ways.reserve(num_ways.size() + result.size());      // reverse from google 
                num_ways.insert(num_ways.end(), result.begin(), result.end());      
            }
        }
    }
    return num_ways;
}

int num_digits(int num){        // helper function to determine the number of digits
    return (int)(log10(num) + 1);       // from an old class 
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    unsigned int ways_length = ways.size();      // The length of ways it can be done 
    int max_width = num_digits(ways_length);        // the legnth of the greatest intiger
    
    if ( ways_length > 10) { // check if its greater then ten for the allignment 
        for (size_t r = 1; r <= ways_length; r++){
            cout << setw(max_width) << r << ". [";
            for (size_t c = 1; c <= ways.at(r - 1).size(); c++){        // "ways[r - 1].size() gets the number of digits inside
                cout << ways.at(r - 1).at(c - 1);       // at() to get element from r - 1 and c - 1 position 
                if (c != ways.at(r - 1).size()){       // check if its not the last digit 
                    cout << ", ";
                }else{
                    cout << "]" << endl;
                }
            }
            
        }
    } else {        // less then 10 
        for (size_t r = 1; r <= ways_length; r++){
            cout << r << ". [";
            for (size_t c = 1; c <= ways.at(r - 1).size(); c++){
                cout << ways.at(r - 1).at(c - 1);
                if (c != ways.at(r - 1).size()){
                    cout << ", ";;
                }else{
                    cout << "]" << endl;
                }
            }
        }
        
    }
}

int main(int argc, char * const argv[]) 
{
    if (argc != 2){         // check the number of arguments
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    if (atoi(argv[1]) <= 0 || atoi(argv[1]) != (int)atoi(argv[1]) ){    // check if its not a int and not a positive intiger
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    int stair_cnt = atoi(argv[1]);
    vector<vector<int> > diff_ways = get_ways(stair_cnt);
    
    if (stair_cnt == 1){        // grammer for just one step 
        cout << diff_ways.size() << " way to climb " << stair_cnt << " stair." << endl;
        display_ways(diff_ways);
    }else{        // grammer for more then one step 
        cout << diff_ways.size() << " ways to climb " << stair_cnt << " stairs." << endl;
        display_ways(diff_ways);
    }
    return 0;
}
