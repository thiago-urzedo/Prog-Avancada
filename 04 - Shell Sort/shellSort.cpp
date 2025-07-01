#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream> 

using namespace std;

void moveTurtleToTop(vector<string>&, int);

int main() {
    ifstream input;
    
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    int nTests, nTurtles;
    vector<string> original, desired, output;
    string line;

    // Lê o número de testes
    getline(input, line);
    istringstream(line) >> nTests;

    for (int i = 0; i < nTests; i++) {
        // Lê o número a quantidade de tartarugas
        getline(input, line);
        istringstream(line) >> nTurtles;
        
        int j;
        j = 0;

        // Até a metade da lista, lê o nome das tartarugas e as salva na pilha original.
        // Da metade pra frete, salva na pilha desejada
        while (j < nTurtles*2) {
            getline(input, line);
            
            if (j < nTurtles) {
                original.push_back(line);
            } else {
                desired.push_back(line);
            }
            j++;
        }

        // Itera as duas pilhas e verifica se os valores são diferentes,
        // caso sejam, move a tartaruga para o topo e a adiciona no vetor de resposta
        int k = nTurtles-1;
        while(k >= 0) {
            if (original[k].compare(desired[k]) == 0) {
                k--;
            } else {
                output.push_back(original[k]);
                moveTurtleToTop(original, k);
            }
        }

        // Caso a tartaruga se encontre no vetor de resposta, imprime o seu nome
        for (int index = nTurtles - 1; index >= 0; index--) {
            if (find(output.begin(), output.end(), desired[index]) != output.end()) {
                cout << desired[index] << endl;
            }
        }

        cout << endl;
        original.clear();
        desired.clear();
        output.clear();
    }

    input.close();

    return 0;
}

// Função utilizada para mover a tartaruga para o topo do vetor
void moveTurtleToTop(vector<string>& arr, int index) {
    string aux = arr[index];
    
    for (int i = index; i > 0; i--) {
        arr[i] = arr[i-1];
    }

    arr[0] = aux;
}
