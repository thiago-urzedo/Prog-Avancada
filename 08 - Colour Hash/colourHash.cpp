#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <unordered_set>
#include <fstream>

using namespace std;

struct State {
    array<int, 24> conf; // configuração do puzzle (24 inteiros)
    string moves; // sequência de movimentos
};

// Array com o estado objetivo final
array<int,24> FINAL = {
    0,3,4,3,0,5,6,5,0,1,2,1,
    0,7,8,7,0,9,10,9,0,1,2,1
};

array<int,24> rotateLeftCW(const array<int,24>& s);
array<int,24> rotateLeftCCW(const array<int,24>& s);
array<int,24> rotateRightCW(const array<int,24>& s);
array<int,24> rotateRightCCW(const array<int,24>& s);
bool isFinal(const array<int,24>& s);
string bfs(array<int,24> start);

int main() {
    ifstream input;

    // Se não encontrar o arquivo de entrada, o programa termina
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    int n;
    input >> n;

    for (int i = 0; i < n; i++) {
        array<int, 24> conf;

        for (int k = 0; k < 24; k++) {
            input >> conf[k];
        } 

        cout << bfs(conf) << "\n";
    }

    return 0;
}

// Rotação da esquerda (horário)
array<int,24> rotateLeftCW(const array<int,24>& s) {
    array<int,24> t = s;
    for (int i=0;i<12;i++) t[i] = s[(i+11)%12]; // shift no sentido horário
    for (int i=12;i<24;i++) t[i] = s[i];       // direita fica igual
    return t;
}

// Rotação da esquerda (anti-horário)
array<int,24> rotateLeftCCW(const array<int,24>& s) {
    array<int,24> t = s;
    for (int i=0;i<12;i++) t[i] = s[(i+1)%12]; // shift no sentido anti-horário
    for (int i=12;i<24;i++) t[i] = s[i];
    return t;
}

// Rotação da direita (horário)
array<int,24> rotateRightCW(const array<int,24>& s) {
    array<int,24> t = s;
    for (int i=12;i<24;i++) t[i] = s[(i-1<12?23:i-1)]; // shift no sentido horário
    for (int i=0;i<12;i++) t[i] = s[i];
    return t;
}

// Rotação da direita (anti-horário)
array<int,24> rotateRightCCW(const array<int,24>& s) {
    array<int,24> t = s;
    for (int i=12;i<24;i++) t[i] = s[(i+1>23?12:i+1)]; // shift no sentido anti-horário
    for (int i=0;i<12;i++) t[i] = s[i];
    return t;
}

// Verifica se o estado atual é igual ao estado final
bool isFinal(const array<int,24>& s) {
    return s == FINAL;
}

// Função da BFS (Busca em largura)
string bfs(array<int,24> start) {
    if (isFinal(start)) return "PUZZLE ALREADY SOLVED";

    queue<State> q;
    unordered_set<string> visited;

    // compacta o vetor em uma string
    auto toStr = [](const array<int,24>& s) {
        string r;
        for (int x : s) r += (char)(x + 'A');
        return r;
    };

    string startStr = toStr(start);
    visited.insert(startStr);
    q.push({start, ""});

    while (!q.empty()) {
        auto cur = q.front(); q.pop();

        if (cur.moves.size() >= 16) continue;

        vector<pair<array<int,24>,char>> nexts;
        nexts.push_back({rotateLeftCW(cur.conf),'1'});
        nexts.push_back({rotateRightCW(cur.conf),'2'});
        nexts.push_back({rotateLeftCCW(cur.conf),'3'});
        nexts.push_back({rotateRightCCW(cur.conf),'4'});

        for (auto &nx : nexts) {
            auto st = nx.first;
            string code = toStr(st);
            if (visited.count(code)) continue;
            visited.insert(code);
            string nm = cur.moves + nx.second;
            if (isFinal(st)) return nm;
            q.push({st, nm});
        }
    }
    
    return "NO SOLUTION WAS FOUND IN 16 STEPS";
}
