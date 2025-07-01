#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Estrutura que representa um time
struct Team {
    int id = 0;                       // ID do time (de 1 a 100)
    int solved = 0;                   // Quantidade de problemas resolvidos
    int penalty = 0;                  // Tempo total com penalidade
    bool submitted = false;           // Indica se o time fez alguma submissão
    int wrong[10] = {0};              // Tentativas erradas por problema (índice 1–9)
    bool solvedProblem[10] = {false}; // Se o problema já foi resolvido corretamente
};

bool compare(const Team&, const Team&);
void processCase(vector<string>&, int&);

int main() {
    ifstream input;
    
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    string line;

    // Lê o número de casos de teste
    int T;
    getline(input, line);
    istringstream(line) >> T;

    // Consome a linha em branco após o número de casos
    while (getline(input, line) && line.empty());

    int currentCase = 0;
    vector<string> submissions;

    // Processa a entrada linha por linha
    do {
        if (line.empty()) {
            // Linha em branco indica fim do caso atual
            if (!submissions.empty()) {
                processCase(submissions, currentCase);
                submissions.clear();
            }
        } else {
            // Adiciona a linha de submissão ao caso atual
            submissions.push_back(line);
        }
    } while (getline(input, line)); // Continua lendo até o fim do arquivo

    // Processa o último caso se não terminou com linha em branco
    if (!submissions.empty() && currentCase < T) {
        processCase(submissions, currentCase);
    }

    input.close();

    return 0;
}

// Função de comparação usada para ordenar o placar
bool compare(const Team& a, const Team& b) {
    if (a.solved != b.solved)
        return a.solved > b.solved;         // Mais problemas resolvidos primeiro
    if (a.penalty != b.penalty)
        return a.penalty < b.penalty;       // Menor tempo total em caso de empate
    
    return a.id < b.id;                     // Menor ID do time em caso de empate
}

// Função que processa um caso de teste completo
void processCase(vector<string>& submissions, int& testCase) {
    vector<Team> teams(101); // Times de ID 1 a 100

    // Processa cada linha de submissão
    for (const string& line : submissions) {
        istringstream ss(line);
        int tid, pid, time;
        char verdict;
        ss >> tid >> pid >> time >> verdict;

        Team& team = teams[tid];
        team.id = tid;
        team.submitted = true; // Marca que esse time participou

        if (verdict == 'C') { // Submissão correta
            if (!team.solvedProblem[pid]) {
                team.solved++;
                team.penalty += time + team.wrong[pid] * 20;
                team.solvedProblem[pid] = true;
            }
        } else if (verdict == 'I') { // Submissão incorreta
            if (!team.solvedProblem[pid]) {
                team.wrong[pid]++;
            }
        }
        // Submissões com R, U, E são ignoradas
    }

    // Cria o placar final com os times que participaram
    vector<Team> scoreboard;
    for (int i = 1; i <= 100; ++i) {
        if (teams[i].submitted)
            scoreboard.push_back(teams[i]);
    }

    // Ordena os times conforme a regra do problema
    sort(scoreboard.begin(), scoreboard.end(), compare);

    // Imprime linha em branco entre os casos (exceto o primeiro)
    if (testCase++ > 0) cout << endl;

    // Exibe o placar do caso atual
    for (const auto& t : scoreboard) {
        cout << t.id << " " << t.solved << " " << t.penalty << endl;
    }
}
