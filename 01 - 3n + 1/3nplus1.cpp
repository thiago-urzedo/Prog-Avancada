#include <iostream>

using namespace std;

int main ()
{
    int n, m;

    while (cin >> n >> m) {
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
