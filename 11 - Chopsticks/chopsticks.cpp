#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9+7;

int main() {
    int k, n;
    cin >> k >> n;
    vector<int> L(n + 1); // 1-based indexing

    for (int i = 1; i <= n; ++i)
        cin >> L[i];

    // Ordenar os hashis do menor para o maior
    sort(L.begin() + 1, L.end());

    // dp[i][j] = menor custo para formar j pares com os primeiros i hashis
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));

    // Nenhum par com 0 hashis ⇒ custo zero
    for (int i = 0; i <= n; ++i)
        dp[i][0] = 0;

    // Preenche a tabela
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            // Caso 1: ignora o i-ésimo hashi
            dp[i][j] = dp[i - 1][j];

            // Caso 2: usa os hashis i e i-1 para formar um par
            int diff = L[i] - L[i - 1];
            if (i >= 2 && dp[i - 2][j - 1] != INF)
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 1] + diff * diff);
        }
    }

    cout << dp[n][k] << endl;
    return 0;
}
