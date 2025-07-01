#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void solve(int n, int m) {
    int left_n = 0, left_d = 1;
    int right_n = 1, right_d = 0;
    int curr_n = 1, curr_d = 1;

    string path;

    while (!(curr_n == n && curr_d == m)) {
        if ((long long)curr_n * m < (long long)n * curr_d) {
            // Atual é menor que o alvo -> vá para direita
            path += 'R';
            left_n = curr_n;
            left_d = curr_d;
        } else {
            // Atual é maior -> vá para esquerda
            path += 'L';
            right_n = curr_n;
            right_d = curr_d;
        }

        // novo mediador
        curr_n = left_n + right_n;
        curr_d = left_d + right_d;
    }

    cout << path << endl;
}

int main() {
    ifstream infile("input.txt");
    int n, m;

    while (infile >> n >> m) {
        if (n == 1 && m == 1) break;
        solve(n, m);
    }

    return 0;
}
