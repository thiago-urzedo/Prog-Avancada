#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int center_indices[8] = {6, 7, 8, 11, 12, 15, 16, 17};
const int move_order[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};

string moves = "ABCDEFGH";

vector<int> board(24), temp_board(24);
string solution;
bool solved = false;

int cost() {
    int count[6] = {0}; // cores 1 a 5
    for (int i : center_indices)
        count[board[i]]++;
    return 8 - *max_element(count + 1, count + 6); // cores são de 1 a 5
}

void rotate(int m) {
    int tmp[7];
    for (int i = 0; i < 7; ++i)
        tmp[i] = board[move_order[m][i]];

    // Rotação: último valor vai para o primeiro
    for (int i = 0; i < 7; ++i)
        board[move_order[m][i]] = tmp[(i + 1) % 7];
}

bool dfs(int depth, int max_depth, string path) {
    if (cost() == 0) {
        solution = path;
        solved = true;
        return true;
    }

    if (depth + cost() > max_depth) return false;

    vector<int> snapshot = board;

    for (int i = 0; i < 8; ++i) {
        rotate(i);
        if (dfs(depth + 1, max_depth, path + moves[i])) return true;
        board = snapshot; // desfaz rotação
    }
    return false;
}

int main() {
    ifstream input;

    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    int n;
    input >> n;

    for(int i = 0; i < n; i++) {
        board.clear();
        board.resize(24);

        for (int i = 0; i < 24; ++i) {
            input >> board[i];
        }

        solved = false;
        solution.clear();

        for (int depth = 0; depth <= 10; ++depth) {
            if (dfs(0, depth, "")) break;
        }

        if (solved)
            cout << solution << endl;
        else
            cout << "NO SOLUTION WAS FOUND IN 10 STEPS" << endl;
    }
    return 0;
}
