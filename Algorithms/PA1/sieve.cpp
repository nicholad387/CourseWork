/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : 
 * Date        : September 16, 2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
            
    for (int i = 0; i <= limit_; i++){ 
        is_prime_[i] = true;
    }
    
    sieve();
    
    num_primes_ = count_num_primes();
    for(int i = limit_; i > 0; i--){ // finds the largest prime
        if (is_prime_[i] == true){
            max_prime_ = i;
            break;
        }
    }
    
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_), 
        primes_per_row = 80 / (max_prime_width + 1); 
    int current_row_num = 0; // what is currently printed in the row
    int num_printed = 0; // total primes printed to the screen
    if (num_primes_ >= primes_per_row){
        for (int i = 2; i <=limit_; i++){
            if (current_row_num < primes_per_row){
                if (is_prime_[i] == true){
                    cout << setw(max_prime_width) << i;
                    current_row_num ++;
                    num_printed ++;
                    if (num_printed + 1 <= num_primes_ && current_row_num != primes_per_row){ // check if its the last number in the row
                        cout << " ";
                    }
                }
            }else{
                cout << endl;
                current_row_num = 0;
            }
        }
    }else{
        for (int i = 2; i <= limit_; i++){
            if (is_prime_[i] == true){
                cout << i ;
                num_printed ++;
                if (num_printed + 1 <= num_primes_){ // check if its the last number or not
                    cout << " ";
                }
            }
            
        }
    }
    
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int num_primes = 0;
    
    for (int i = 2; i <= limit_; i ++){
        if (is_prime_[i] == true){
            num_primes ++;
        }
    }
    return num_primes;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for (int i = 2; i <= sqrt(limit_); i++){
        if (is_prime_[i] == true){
            for (int c = i*i; c <= limit_; c += i){
                is_prime_[c] = false;
            }
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digit = 0;
    while (num >=1){
        num = num / 10;
        digit ++;
    }
    return digit;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve primes(limit);
    cout << endl;
    cout << "Number of primes found: " << primes.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    primes.display_primes();
    
    return 0;
}
