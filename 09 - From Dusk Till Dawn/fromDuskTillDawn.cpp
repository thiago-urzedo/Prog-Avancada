#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

struct Edge {
    int to;       // destino
    int dep_nt;   // hora de partida normalizada para [0..11]
    int dur;      // duração em horas (chegada_nt = dep_nt + dur <= 11)
};

struct NodeState {
    int nights;   // noites gastas
    int time_nt;  // hora dentro da noite [0..11]
    int u;        // cidade
    bool operator<(const NodeState& other) const {
        if (nights != other.nights) return nights > other.nights; // min-heap via > 
        return time_nt > other.time_nt; // em empate, chegar mais cedo é melhor
    }
};

static inline bool isNightHour(int h);
static inline int nightTime(int h);
static inline bool normalizeNightFlight(int dep, int dur, int &dep_nt_out);

int main() {
    ifstream input;

    // Se não encontrar o arquivo de entrada, o programa termina
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    int n_tests;
    input >> n_tests;

    for (int tc = 0; tc < n_tests; tc++) {
        int m; 
        input >> m;
        unordered_map<string,int> id;
        vector<vector<Edge>> g; 
        auto getId = [&](const string& s) {
            auto it = id.find(s);
            if (it != id.end()) return it->second;
            int nid = (int)id.size();
            id[s] = nid;
            g.emplace_back();
            return nid;
        };

        for (int i = 0; i < m; ++i) {
            string a, b;
            int dep, dur;
            input >> a >> b >> dep >> dur;
            int dep_nt;
            if (normalizeNightFlight(dep, dur, dep_nt)) {
                int u = getId(a);
                int v = getId(b);
                g[u].push_back({v, dep_nt, dur});
            }
        }

        string srcName, dstName;
        if (!(input >> srcName >> dstName)) break;

        cout << "Test Case " << (tc+1) << ".\n";

        if (id.find(srcName) == id.end() || id.find(dstName) == id.end()) {
            cout << "There is no route Vladimir can take.\n";
            continue;
        }

        int n = (int)g.size();
        int s = id[srcName], t = id[dstName];

        // Dijkstra em (nights, time_nt). Mantemos o melhor par para cada cidade.
        const int INF = 1e9;
        vector<int> bestN(n, INF);
        vector<int> bestTime(n, INF);

        priority_queue<NodeState> pq;
        bestN[s] = 0;
        bestTime[s] = 0; // começa às 18:00 (nt = 0)
        pq.push({0, 0, s});

        int answer = -1;

        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            int u = cur.u, nights = cur.nights, time_nt = cur.time_nt;

            if (nights > bestN[u]) continue;
            if (nights == bestN[u] && time_nt > bestTime[u]) continue;

            if (u == t) { 
                answer = nights; 
                break; 
            }

            for (const auto& e : g[u]) {
                int addNight = (e.dep_nt >= time_nt) ? 0 : 1;
                int nn = nights + addNight;
                int nt = e.dep_nt + e.dur; // chegada na mesma linha do tempo noturna (<=11 por construção)

                if (nn < bestN[e.to] || (nn == bestN[e.to] && nt < bestTime[e.to])) {
                    bestN[e.to] = nn;
                    bestTime[e.to] = nt;
                    pq.push({nn, nt, e.to});
                }
            }
        }

        if (answer < 0) {
            cout << "There is no route Vladimir can take.\n";
        } else {
            cout << "Vladimir needs " << answer << " litre(s) of blood.\n";
        }
        
    }


    return 0;
}

// Varifica se a hora de entrada é "noturna"
static inline bool isNightHour(int h) {
    return (h >= 18 || h <= 5);
}

// Mapeia hora real (0..23) para "tempo noturno" 0..11.
// 18->0,19->1,...,23->5, 0->6,...,5->11.
static inline int nightTime(int h) {
    if (h >= 18) return h - 18;
    // 0..5
    return h + 6;
}

// Verifica se um voo (partida, dur) é totalmente noturno
// e retorna (dep_nt, dur) prontos para uso se válido.
static inline bool normalizeNightFlight(int dep, int dur, int &dep_nt_out) {
    if (!isNightHour(dep)) return false; // parte de dia -> inválido
    if (dep >= 18) {
        // Parte 18..23, pode cruzar meia-noite: chegada deve ser <= 6
        // (dep + dur) % 24 <= 6 equivale a dur <= (24 - dep) + 6
        int maxDur = (24 - dep) + 6; // tempo noturno restante até 06:00
        if (dur > maxDur) return false;
    } else { // 0..5
        // Deve terminar até 06:00 do mesmo período noturno
        int maxDur = 6 - dep;
        if (dur > maxDur) return false;
    }
    dep_nt_out = nightTime(dep);
    // chegada_nt = dep_nt + dur (por validade, <= 11)
    if (dep_nt_out + dur > 11) return false;
    return true;
}
