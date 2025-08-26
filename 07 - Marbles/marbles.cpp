#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Definição de tipo e variáveis globais, onde x é o número de
// caixas do tipo 1, y o número de caixas do tipo 2 e d
#define ll long long
ll x, y, d;

// Definição da função do Algoritimo de Euclides Estendido
void extendedEuclid(ll, ll);

int main() {
    ifstream input;

    // Se não encontrar o arquivo de entrada, o programa termina
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
    }

    ll v, n1, n2, c1, c2;
    
    // Lê a quantidade v de bolinhas de gude, o programa termina
    // quando for igual a 0
    input >> v;
    while(v != 0) {
        input >> c1 >> n1 >> c2 >> n2;
        
        // Calcula o MDC(a,b)
        extendedEuclid(n1,n2);
        
        // Para que exista solução, v precisa ser divisível pelo MDC(a,b)
        if (v%d != 0) {
            cout << "failed" << endl;
        } else {
            // para chegar em ax + by = v
            x *= v/d;
            y *= v/d;
            // Duas equações Diofantina Lineares
            // x = x0 + (b/d)n
            // y = y0 − (a/d)n
            // onde n é inteiro

            // derivação de n, baseado no fato de x e y possuirem valores positivos
            // x0 + (b/d)n >= 0, resolvendo para n: teremos n >= -x0*d/b
            // y0 - (a/d)n >= 0, resolvendo para n: teremos n <= y0*a/b
            // juntando -> x0*d/b <= n <= y0*d/b
            n2 /= d, n1 /= d;
            ll lowerbound = ceil(-(double)x/n2);
            ll upperbound = floor((double)y/n1);

            if (lowerbound <= upperbound) {
                // compara o custo para determinar a melhor solução
                ll res1 = c1*(x+n2*lowerbound) + c2*(y-n1*lowerbound);
                ll res2 = c1*(x+n2*upperbound) + c2*(y-n1*upperbound);

                if (res1 < res2) {
                    cout << (x+n2*lowerbound) << " " << (y-n1*lowerbound) << endl;
                } else {
                    cout << (x+n2*upperbound) << " " << (y-n1*upperbound) << endl;
                }
            } else {
                cout << "failed" << endl;
            }
        }

        input >> v;
    }

    input.close();

    return 0;
}

// Algoritimo de Euclides Estendido, que encontra o MDC de a e b, e determina os inteiros
// x e y que satisfazem a Relação de Bézout: ax + by = MDC(a, b)
void extendedEuclid(ll a, ll b) {
    if (b==0) {
        x=1; 
        y=0; 
        d=a; 
        return;
    }

    extendedEuclid(b, a%b);
    
    ll y1 = x-(a/b)*y;
    x = y;
    y = y1;
}
