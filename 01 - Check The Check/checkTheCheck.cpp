#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    char square;
    ifstream input;
    
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }
    
    bool exit = false;
    while (!exit) {
        vector<vector<char>> board(8, vector<char>(8));
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                input.get(square);
                if (square == '\n' || square == ' ') {
                    i--;
                    continue;
                }
                cout << square << " ";
            }
            cout << endl;
            input.get(square);
            if (input.eof()) {
                exit = true;
                break;
            }
        }
    }
    
    input.close();

    return 0;
}
