#include <iostream>

using namespace std;

unsigned int reverseNumber(unsigned int number);
bool checkPalindrome(unsigned int number);

int main() {
    unsigned int number, reversed, iterations;
    reversed = iterations = 0;
    
    cin >> number;
    if (number < 10) return 0;

    do {
        reversed = reverseNumber(number);
        number = number + reversed;
        iterations++;
    } while(!checkPalindrome(number) && number < UINT32_MAX && iterations < 1000);

    if (iterations < 1000 && number < UINT32_MAX) {
        cout << iterations << " " << number << endl;
    }

    return 0;
}

unsigned int reverseNumber(unsigned int number) {
    unsigned int reversed = 0;
    unsigned int remainder = 0;

    while(number != 0) {
        remainder = number % 10;
        reversed = reversed * 10 + remainder;
        number /= 10;
    }

    return reversed;
}

bool checkPalindrome(unsigned int number) {
    return (number == reverseNumber(number));
}
