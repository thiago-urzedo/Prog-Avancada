#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>
#include <fstream>

using namespace std;

const int MAXN = 150;
int graph[MAXN][MAXN];
int parent[MAXN];
int M, N;

bool bfs(int s, int t);
int edmondsKarp(int s, int t);

int main() {
    ifstream input;

    // Se não encontrar o arquivo de entrada, o programa termina
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    while (input >> M >> N) {
        if (M == 0 && N == 0) break;
        
        int total_members = 0;
        vector<int> teams(M);
        vector<int> tables(N);
        
        for (int i = 0; i < M; i++) {
            input >> teams[i];
            total_members += teams[i];
        }
        
        for (int i = 0; i < N; i++) {
            input >> tables[i];
        }

        // Constroi a estrutura do grafo: Nó 0 até M+N+1
        int s = 0, t = M + N + 1;
        memset(graph, 0, sizeof(graph));
        
        // Conecta o nó de entrada com as equipes
        for (int i = 1; i <= M; i++) {
            graph[s][i] = teams[i-1];
        }
        
        // Conecta cada time às mesas, com capacidade igual a 1
        for (int i = 1; i <= M; i++) {
            for (int j = M+1; j <= M+N; j++) {
                graph[i][j] = 1;
            }
        }
        
        // Conecta as mesas ao destino
        for (int j = M+1; j <= M+N; j++) {
            graph[j][t] = tables[j - M - 1];
        }

        int max_flow = edmondsKarp(s, t);
        
        if (max_flow != total_members) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
            // Para cada time, acha uma mesa com fluxo
            for (int i = 1; i <= M; i++) {
                vector<int> assigned;

                // se houver caminho de i para j, mas no grafo residual a aresta reversa
                // j->i for positiva, então há caminho de i para j
                for (int j = M+1; j <= M+N; j++) {
                    if (graph[j][i] > 0) {
                        assigned.push_back(j - M);
                    }
                }
                
                // Imprime as mesas para cada time
                for (unsigned int k = 0; k < assigned.size(); k++) {
                    if (k) cout << " ";
                    cout << assigned[k];
                }
                cout << endl;
            }
        }
    }

    input.close();

    return 0;
}

// Implementação da BFS (busca em largura)
bool bfs(int s, int t) {
    bool visited[MAXN];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v <= t; v++) {
            if (!visited[v] && graph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    
    return visited[t];
}

// Implementação do algoritmo de Edmonds-Karp, para calcular o 
// fluxo máximo no grafo
int edmondsKarp(int s, int t) {
    int max_flow = 0;
    
    while (bfs(s, t)) {
        int path_flow = INT_MAX;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, graph[u][v]);
        }
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }
        
        max_flow += path_flow;
    }

    return max_flow;
}
