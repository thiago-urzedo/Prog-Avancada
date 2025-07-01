#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Variável global que representa um tabuleiro 8x8
vector<vector<char>> board(8, vector<char>(8));

bool isInCheck(bool);
bool inBounds(int, int);
bool isAttackedByPawn(int, int, bool);
bool isAttackedByKnight(int, int, bool);
bool isAttackedByLinePiece(int, int, bool, vector<pair<int, int>>, string);

int main() {

    ifstream input;
    
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }
    
    string line;
    int game = 1;
    
    while (true) {
        bool exit = true;

        // Faz a leitura das peças do tabuleiro até que ele esteja vazio
        for (int i = 0; i < 8; i++) {
            getline(input, line);
            if (input.eof()) return 0;

            for (int j = 0; j < 8; j++) {
                board[i][j] = line[j];
                
                if (line[j] != '.') {
                    exit = false;
                }
            }
        }

        if (exit) break;

        // Faz a verificação das peças e mostra o resultado
        bool whiteInCheck = isInCheck(true);
        bool blackInCheck = isInCheck(false);

        cout << "Game #" << game++ << ": ";
        if (whiteInCheck)
            cout << "white king is in check." << endl;
        else if (blackInCheck)
            cout << "black king is in check." << endl;
        else
            cout << "no king is in check." << endl;

        // Faz a leitura da linha vazia entre os tabuleiros
        getline(input, line);
    }
    
    input.close();

    return 0;
}

// Função principal que encontra o rei e chama as verificações para saber se há algum rei em check
bool isInCheck(bool white) {
    // Armazena as coordenadas do rei
    int kx = -1, ky = -1;

    // Encontra o rei
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == 'K' || board[i][j] == 'k') {
                kx = i;
                ky = j;
                break;
            }
        }
    }
    
    // Caso o rei não seja encontrado, houve um erro na leitura do arquivo
    if (kx == -1 || ky == -1) return false;

    // Verifica ataques de peões
    if (isAttackedByPawn(kx, ky, white)) return true;
    
    // Verifica ataques de cavalos
    if (isAttackedByKnight(kx, ky, white)) return true;

    // Verifica ataques de torre ou rainha (linhas e colunas)
    vector<pair<int, int>> rookDirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    if (isAttackedByLinePiece(kx, ky, white, rookDirs, white ? "rq" : "RQ")) return true;

    // Verifica ataques de bispo ou rainha (diagonais)
    vector<pair<int, int>> bishopDirs = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    if (isAttackedByLinePiece(kx, ky, white, bishopDirs, white ? "bq" : "BQ")) return true;

    return false;
}

// Função auxiliar que verifica se as coordenadas passadas por parâmetro 
// se encontram dentro do tabuleiro 8x8, ou seja, tenham valores de 0 até 7
bool inBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

// Função que verifica se o rei está em check por um peão.
// Os peões só atacam na diagonal, apenas 1 unidade para frente
bool isAttackedByPawn(int x, int y, bool white) {
    int dir = white ? -1 : 1;
    int px[] = {x + dir, x + dir};
    int py[] = {y - 1, y + 1};

    for (int i = 0; i < 2; ++i) {
        if (inBounds(px[i], py[i])) {
            if (white && board[px[i]][py[i]] == 'p') return true;
            if (!white && board[px[i]][py[i]] == 'P') return true;
        }
    }

    return false;
}

// Função que verifica se o rei está em check por um cavalo.
// Os cavalos se movem em L e comem as peças que se encontram no destino de seu movimento,
// então há 8 posições possíveis para que um rei esteja em check
bool isAttackedByKnight(int x, int y, bool white) {
    int dxKnight[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dyKnight[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; ++i) {
        int nx = x + dxKnight[i];
        int ny = y + dyKnight[i];

        if (inBounds(nx, ny)) {
            char piece = board[nx][ny];

            if (white && piece == 'n') return true;
            if (!white && piece == 'N') return true;
        }
    }

    return false;
}

// Função que verifica se o rei está em check por peças que se movem em linha reta (torres, bispos e rainhas).
// Recebe a direção do movimento e percorre o tabuleiro nesta direção até "bater" numa peça ou sair do tabuleiro
bool isAttackedByLinePiece(int x, int y, bool white, vector<pair<int, int>> directions, string targets) {
    for (auto [dx, dy] : directions) {
        int nx = x + dx, ny = y + dy;
        
        while (inBounds(nx, ny)) {
            char piece = board[nx][ny];
            
            if (piece == '.') {
                nx += dx;
                ny += dy;

                continue;
            }
            
            if (white && islower(piece) && targets.find(piece) != string::npos) return true;
            if (!white && isupper(piece) && targets.find(piece) != string::npos) return true;
            
            break;
        }
    }

    return false;
}
