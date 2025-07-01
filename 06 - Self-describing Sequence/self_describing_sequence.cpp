#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int golombSequence(int, vector<int>&);

int main() {
    ifstream input;
    
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    int n;
    
    while (true) {
        // Lê um número da entrada até encontrar um zero
        input >> n;
        if (n == 0) break;

        // Vetor usado para memorization, a fim de acelerar o tempo de execução
        vector<int> memo(n+1, 0);

        cout << golombSequence(n, memo) << endl;
    }

    input.close();

    return 0;
}

// Função recursiva para calcular a sequência de Solomon Golomb representada pela forma:
// G(1) = 1
// G(n) = 1 + G(n - G(G(n-1)))
int golombSequence(int n, vector<int>& memo) {
    if (n == 1) {
        return 1;
    } 

    if (memo[n] != 0) {
        return memo[n];
    }

    memo[n] = 1 + golombSequence(n - golombSequence(golombSequence(n-1, memo), memo), memo);
    
    return memo[n];
}
