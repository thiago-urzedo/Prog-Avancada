#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>

using namespace std;

const int INF = INT_MAX;

int main() {
    ifstream input;

    // Se não encontrar o arquivo de entrada, o programa termina
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    // Número de casos de testes
    int T;
    input >> T;

    while (T--) {
        int K, N;
        input >> K >> N;
        K += 8;
        vector<int> L(N+1);

        // Lê as entradas
        for (int i = 1; i <= N; i++) {
            input >> L[i];
        }

        // Inicializa a tabela dp (programação dinâmica) de dimensões [N+2][K+1]
        vector<vector<int>> dp(N+2, vector<int>(K+1, INF));
        for (int i = 0; i <= N+1; i++) {
            dp[i][0] = 0;
        }

        for (int i = N; i >= 1; i--) {
            for (int j = 1; j <= K; j++) {
                // Quando não ha chopsticks suficientes para formar j conjuntos
                if (3*j > (N - i + 1)) {
                    continue;
                }

                // Não usar o chopstick i
                dp[i][j] = dp[i+1][j];

                // User os chopsticks i and i+1 como chopsticks curtos
                // e um i+2 para N, como longo
                if (i+2 <= N+1) {
                    int cost = (L[i+1] - L[i]) * (L[i+1] - L[i]);
                    
                    if (dp[i+2][j-1] != INF) {
                        dp[i][j] = min(dp[i][j], dp[i+2][j-1] + cost);
                    }
                }
            }
        }

        cout << dp[1][K] << endl;
    }

    input.close();

    return 0;
}
