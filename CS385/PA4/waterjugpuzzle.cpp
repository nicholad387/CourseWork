/*******************************************************************************
* Name        : waterjugpuzzle.cpp
* Author      :  Nicholas Mohamed && Narissa 
* Date        : October 14, 2022
* Description : Lists the number of ways to climb n stairs.
* Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;
// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) :
    a { _a }, b { _b }, c { _c }, directions { _directions }, parent {
        nullptr } {
        }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void print_results(State end_state) { //need to rereference something in loop
    
    cout << end_state.directions;
}
void bfs_jugs(State cap, State init, State goal){
    vector<vector<bool>> check; //initalizing 2D 'array' to keep track of visited
    for (int i=0; i<=cap.a; i++) {
        vector<bool> in;
        for (int j=0; j<=cap.b; j++) {
            in.push_back(false);
        }
        check.push_back(in);
    }
    string direc;
    queue<State> q;
    q.push(init);
    State *curr = new State(init);
    int a, b, c;
    int amount_poured;
    bool reached_goal = false;
    while(!(q.empty())){
        *curr = q.front();
        q.pop();
        a = curr->a;
        b = curr->b;
        c = curr->c;
        check[a][b] = true;
        if ((a == goal.a) && (b == goal.b) && (c == goal.c)) { //if reached goal, print trace
            print_results(*curr);
            reached_goal = true;
            return; //stop looping
        }
        //C to A
        if (curr->a <= goal.a && c > 0) {
            a = curr->c + curr->a;
            if (a > cap.a) {
                a = cap.a;
            }
            amount_poured = a - curr->a;
            c = curr->c - amount_poured;
            if (!(check[a][b])) {
                State CtoA(a, b, c, "");
                if (amount_poured > 1) {
                    direc = "\nPour " + to_string(amount_poured) + " gallons from C to A. " + CtoA.to_string();
                } else { "\nPour 1 gallon from C to A. " + CtoA.to_string(); }
                direc = curr->directions + direc;
                CtoA.directions = direc;
                q.push(CtoA);
                check[a][b] = true;
                //cout << CtoA.to_string() << endl;
            }
            direc.clear();
            a = curr->a;
            b = curr->b;
            c = curr->c;
        }
        
        // B to A
        if (curr->a <= goal.a && b > 0) {
            a = curr->b + curr->a;
            if (a > cap.a) {
                a = cap.a;
            }
            amount_poured = a - curr->a;
            b = curr->b - amount_poured;
            if (!(check[a][b])) {
                State CtoA(a, b, c, "");
                if (amount_poured > 1) {
                    direc = "\nPour " + to_string(amount_poured) + " gallons from B to A. " + CtoA.to_string();
                } else { "\nPour 1 gallon from B to A. " + CtoA.to_string(); }
                direc = curr->directions + direc;
                CtoA.directions = direc;
                q.push(CtoA);
                check[a][b] = true;
                //cout << CtoA.to_string() << endl;
            }
            direc.clear();
            a = curr->a;
            b = curr->b;
            c = curr->c;
        }
        
        //C to B
        if (curr->b <= goal.b && c > 0) {
            b = curr->c + curr->b;
            if (b > cap.b) {
                b = cap.b;
            }
            amount_poured = b - curr->b;
            c = c - amount_poured;
            if (!(check[a][b])) {
                State CtoA(a, b, c, "");
                if (amount_poured > 1) {
                    direc = "\nPour " + to_string(amount_poured) + " gallons from C to B. " + CtoA.to_string();
                } else { "\nPour 1 gallon from C to B. " + CtoA.to_string(); }
                direc = curr->directions + direc;
                CtoA.directions = direc;
                q.push(CtoA);
                check[a][b] = true;
                //cout << CtoA.to_string() << endl;
            }
            
            direc.clear();
            a = curr->a;
            b = curr->b;
            c = curr->c;
        }
        
        //A to B
        if (b <= goal.b && a >0) {
            b = curr->b + curr->a;
            if (b > cap.b) {
                b = cap.b;
            }
            amount_poured = b - curr->b;
            a = curr->a - amount_poured;
            if (!(check[a][b])) {
                
                State AtoB(a, b, c, "");
                if (amount_poured > 1) {
                    direc = "\nPour " + to_string(amount_poured) + " gallons from A to B. " + AtoB.to_string();
                } else { "\nPour 1 gallon from A to B. " + AtoB.to_string(); }
                direc = curr->directions + direc;
                AtoB.directions = direc;
                q.push(AtoB);
                check[a][b] = true;
                //cout << AtoB.to_string() << endl;
            }
            direc.clear();
            a = curr->a;
            b = curr->b;
            c = curr->c;
        }
        // B to C
        if (curr->c <= goal.c && b > 0) {
            c = curr->b + curr->c;
            if (c > cap.c) {
                c = cap.c;
            }
            amount_poured = c - curr->c;
            b = curr->b - amount_poured;
            if (!(check[a][b])) {
                State CtoA(a, b, c, "");
                if (amount_poured > 1) {
                    direc = "\nPour " + to_string(amount_poured) + " gallons from B to C. " + CtoA.to_string();
                } else { "\nPour 1 gallon from B to C. " + CtoA.to_string(); }
                direc = curr->directions + direc;
                CtoA.directions = direc;
                q.push(CtoA);
                check[a][b] = true;
                //cout << CtoA.to_string() << endl;
            }
            direc.clear();
            a = curr->a;
            b = curr->b;
            c = curr->c;
        }
        // A to C
        if (c <= goal.c && a >0) {
            c = curr->c + curr->a;
            if (c > cap.c) {
                c = cap.c;
            }
            amount_poured = c - curr->c;
            a = a - amount_poured;
            if (!(check[a][b])) {
                State AtoB(a, b, c, "");
                if (amount_poured > 1) {
                    direc = "\nPour " + to_string(amount_poured) + " gallons from A to C. " + AtoB.to_string();
                } else { "\nPour 1 gallon from A to C. " + AtoB.to_string(); }
                direc = curr->directions + direc;
                AtoB.directions = direc;
                q.push(AtoB);
                check[a][b] = true;
                //cout << AtoB.to_string() << endl;
            }
            direc.clear();
        }
        
    }
    delete curr;
    if (!reached_goal) {
        cout << "No solution.";
    }
    
}


int main(int argc, char *argv[]) {
    
    if (argc != 7) {        //error check num of arguments
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    
    int check;      //error check inputs
    vector<int> arr;
    for (size_t i = 1; i <= 6; i++) {
        
        istringstream iss(argv[i]);
        if (!(iss >> check) || check < 0) {
            if (i < 4) {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char) (64 + i) << "." << endl;
            }else{
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << (char)(61 + i) << "." << endl;
            }
            return 1;
        }
        
        if (i == 3 && check == 0){      //error check if c is empty
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char) (64 + i) << "." << endl;
            return 1;
        }
        
        
        arr.push_back(check);
        iss.clear();
    }
    check = 0;
    for (size_t i = 0; i < 3; i++){     // error check cap vs goal
        
        if (arr[i] < arr[i + 3]) {
            cerr << "Error: Goal cannot exceed capacity of jug " << (char)(65 + i) << "." << endl;
            return 1;
        }
        check += arr[i + 3];
    }
    if (arr[2] != check) {      // error check that sums of goal and cap c
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    
    State init = State(0, 0, stoi(argv[3]), "Initial state ");
    init.directions = "Initial state. " + init.to_string();
    State goal = State(stoi(argv[4]), stoi(argv[5]), stoi(argv[6]), "goal state");
    State cap = State(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]), "capacity");
    
    //cout << init->to_string() << endl; //just for testing purposes
    //cout << goal->to_string() << endl;
    
    //TESTING
    //	State second = State(1, 2, 3, "Second");
    //	second.parent = &init;
    //	goal.parent = &second;
    bfs_jugs(cap, init, goal);
    //print_results(goal);
    //cout << finish.to_string() << endl;
    return 0;
}
