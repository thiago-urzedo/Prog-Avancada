/*
Comando usado para compilar:
$ g++ reverseAndAdd.cpp -o reverseAndAdd.out -Wall

Entrada:
3
195
265
750

* A resposta é dada a cada iteração
*/
#include <iostream>
#include <cstdint>

using namespace std;

unsigned int reverseNumber(unsigned int number);
bool checkPalindrome(unsigned int number);

int main() {
    unsigned int n, number, reversed, iterations;

    cin >> n;
    if (n <= 0 || n > 100) return 0;

    for (unsigned int i = 0; i < n; i++) {
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
