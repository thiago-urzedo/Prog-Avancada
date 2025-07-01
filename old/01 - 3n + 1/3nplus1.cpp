/*
Usei como referência as explicações / implementações nestes dois sites:
- https://cplusplus.com/forum/general/199949/
- https://github.com/SaruarChy/Uva-Online-judge-Solution/blob/master/100%20-%20The%203n%20%2B%201%20problem.cpp

Comando usado para compilar:
$ g++ 3nplus1.cpp -o 3np1.out -Wall

Entrada:
1 10
100 200
201 210
900 1000
 */
#include <iostream>

using namespace std;

int main ()
{
    int n, m;

    while (cin >> n >> m) {
        // Condição de parada, os números lidos devem estar entre 0 e 10000
        if (n <= 0 || m <= 0 || n >= 10000 || m >= 10000) {
            break;
        }

        cout << n << " " << m << " ";

        if (n > m) {
            int aux = n;
            n = m;
            m = aux;
        }

        int max_cycle = 0;

        for (int i = n; i <= m; i++) {
            int j = i;
            int cycle = 1;

            while (j != 1) {
                if (j % 2 != 0) {
                    j = (3 * j) + 1;
                } else {
                    j = j / 2;
                }

                cycle++;
            }

            max_cycle = max(max_cycle, cycle);
        }

        cout << max_cycle << endl;
    }

    return 0;
}
