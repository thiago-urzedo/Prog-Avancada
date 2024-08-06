#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

bool checkCarmichaelNumber(int n);

int main() {

    srand(time(NULL));

    int n;

    while (true) {
        cin >> n;
        
        if (n == 0 || n <= 2 || n > 65000) {
            break;
        }

        if (checkCarmichaelNumber(n)) {
            cout << "The number " << n << " is a Carmichael number." << endl;
        } else {
            cout << n << " is normal." << endl;
        }
    }

    return 0;
}

bool checkCarmichaelNumber(int n) {
    bool result = true;

    for (int i = 0; i < 10; i++) {
        int a = rand() % (n-1) + 2;
        result = result && (int)pow(a, n) % n == a;
    }

    return result;
}
