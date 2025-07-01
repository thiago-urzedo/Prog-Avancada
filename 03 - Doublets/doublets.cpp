#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <fstream>

using namespace std;

bool isDoublet(const string&, const string&);
vector<string> bfs(const string&, const string&, const vector<string>&);

int main() {
    ifstream input;
    
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    string line;
    vector<string> dictionary;
    vector<pair<string, string>> queries;

    // Leitura do dicionário
    while (getline(input, line)) {
        if (line.empty()) break;
        dictionary.push_back(line);
    }

    // Leitura das consultas (pares de palavras)
    while (getline(input, line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        string a, b;
        ss >> a >> b;
        queries.push_back({a, b});
    }

    bool first = true;

    // Processa cada consulta
    for (const auto& [start, end] : queries) {
        if (!first) cout << endl;
        first = false;

        vector<string> path = bfs(start, end, dictionary);

        if (path.empty()) {
            cout << "No solution." << endl;
        } else {
            for (const string& word : path)
                cout << word << endl;
        }
    }

    input.close();

    return 0;
}

// Verifica se duas palavras diferem em exatamente uma letra
bool isDoublet(const string& a, const string& b) {
    if (a.length() != b.length()) return false;

    int diff = 0;
    for (size_t i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) {
            diff++;
            if (diff > 1) return false; // mais de uma letra diferente
        }
    }
    return diff == 1;
}

// Realiza BFS para encontrar o menor caminho entre start e end
vector<string> bfs(const string& start, const string& end, const vector<string>& dict) {
    map<string, vector<string>> graph;

    // Constrói o grafo com arestas entre palavras que são doublets
    for (size_t i = 0; i < dict.size(); ++i) {
        for (size_t j = i + 1; j < dict.size(); ++j) {
            if (isDoublet(dict[i], dict[j])) {
                graph[dict[i]].push_back(dict[j]);
                graph[dict[j]].push_back(dict[i]);
            }
        }
    }

    // BFS
    map<string, string> parent;
    queue<string> q;
    set<string> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        string current = q.front(); q.pop();

        for (const string& neighbor : graph[current]) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
                if (neighbor == end) break;
            }
        }
    }

    // Reconstrói o caminho do fim até o início
    vector<string> path;
    if (parent.find(end) == parent.end() && start != end) return {}; // sem caminho

    for (string at = end; at != start; at = parent[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}
