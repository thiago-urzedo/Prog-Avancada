/*
Usei como referência a implementação desse repositório:
- https://github.com/morris821028/UVa/blob/master/volume100/10006%20-%20Carmichael%20Numbers.cpp#L18

Entrada:
1729
17
561
1109
431
0

* A resposta é dada a cada iteração
*/
#include <iostream>
#include <cstdlib>

char Prime[65001] = {};

using namespace std;

void sieve();
long long mod(long long x, long long y, long long m);
int checklNumber(int n);

int main() {

    sieve();
    int n;

    while (true) {
        cin >> n;
        
        if (n == 0 || n <= 2 || n >= 65000) {
            break;
        }

        if (Prime[n] == 1 && checklNumber(n) == 1) {
            cout << "The number " << n << " is a Carmichael number." << endl;
        } else {
            cout << n << " is normal." << endl;
        }
    }

    return 0;
}

void sieve() {
	int i, j;
	for(i = 2; i < 65000; i++) {
		if(Prime[i] == 0) {
			for(j = 2; i*j < 65000; j++)
				Prime[i*j] = 1;
		}
	}
}

long long mod(long long x, long long y, long long m) {
	long long tmp = x, ans = 1;
	while(y) {
		if(y&1) {
			ans *= tmp;
			ans %= m;
		}
		tmp = tmp*tmp, tmp %= m;
		y >>= 1;
	}
	return ans;
}

int checklNumber(int n) {
    int i;
	for(i = 2; i <= n-1; i++) {
		if(mod(i, n, n) != i)
			return 0;
	}
	return 1;
}
