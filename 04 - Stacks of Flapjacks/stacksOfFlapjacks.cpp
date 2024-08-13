/*
Usei como referência a implementação desse repositório:
- https://github.com/morris821028/UVa/blob/master/volume001/120%20-%20Stacks%20of%20Flapjacks.cpp

Comando usado para compilar:
$ g++ stacksOfFlapjacks.cpp -o stacksOfFlapjacks.out -Wall

Entrada:
1 2 3 4 5
5 4 3 2 1
5 1 2 3 4

* A resposta é dada a cada iteração
*/
#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;

int main() {
    string line;
    
    while(getline(cin, line) && !line.empty()) {
        stringstream sin(line);
        int A[1000], n = 0;
        int flip[1000], step = 0;
        int i, j, k, tmp;

        while(sin >> A[n]) {
            n++;
        }

        cout << A[0];

        for(i = 1; i < n; i++) {
            cout << " " << A[i];
        }

        cout << endl;

        for(i = 0; i < n; i++) {
            int idx = n-i-1;

            for(j = 0; j < n-i; j++) {
                if(A[idx] < A[j])
                    idx = j;
            }

            if(idx == n-i-1)
                continue;

            if(idx) {
                flip[step++] = n-idx;
                for(j = 0, k = idx; j < k; j++, k--)
                    tmp = A[j], A[j] = A[k], A[k] = tmp;
            }

            flip[step++] = i+1;

            for(j = 0, k = n-i-1; j < k; j++, k--)
                tmp = A[j], A[j] = A[k], A[k] = tmp;
        }

        for(i = 0; i < step; i++)
            cout << flip[i] << " ";

        cout << "0" << endl;
    }

    return 0;
}
