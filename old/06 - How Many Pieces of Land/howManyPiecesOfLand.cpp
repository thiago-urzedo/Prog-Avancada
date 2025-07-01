/*
Usei o ChatGPT para descobrir a fórmula de como calcular os pedaços.

Comando usado para compilar:
$ g++ reverseAndAdd.cpp -o reverseAndAdd.out -Wall

Entrada:
4
1
2
3
4

* A resposta é dada ao final, depois da execução do programa
*/
#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

int calcPiecesOfLand(int n);

int main() {

    int s;
    vector<int> results;

    cin >> s;

    if (s <= 0 || s >= 3500)
        return 0;

    for(int n = 0; n < s; n++) {
        int aux;
        cin >> aux;
        if (aux < 0 || aux >= INT16_MAX) {
            continue;
        }
        results.push_back(calcPiecesOfLand(aux));
    }

    for (auto r : results) {
        cout << r << endl;
    }

    return 0;
}

int calcPiecesOfLand(int n) {
    return n*(n-1)/2 + n*(n-1)*(n-2)*(n-3)/24 + 1;
}
