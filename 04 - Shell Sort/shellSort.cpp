#include <iostream>
#include <vector>
#include <string>

using namespace std;

void moveTurtleToTop(std::vector<string>&, int);

int main() {
    int nTests, nTurtles;
    vector<string> original, desired;

    cin >> nTests;

    for (int i = 0; i < nTests; i++) {
        cin >> nTurtles;
        
        int j, k;
        j = 0;

        while (j < nTurtles*2) {
            string aux;
            getline(cin, aux);
            
            if (j < nTurtles) {
                original.push_back(aux);
            } else {
                desired.push_back(aux);
            }
            j++;
        }

        j = k = nTurtles-1;
        while(j >= 0 && k >= 0) {
            
            if (original[j] == desired[k]) {
                j--;
                k--;
            } else if (original[j] != desired[k]) {
                cout << original[j] << endl;
                moveTurtleToTop(original, j);
            }
        }

        cout << endl;
        original.clear();
        desired.clear();
    }

    return 0;
}

void moveTurtleToTop(std::vector<string>& arr, int index) {
    
    for (int i = index; i > 0; --i) {
        arr[i] = arr[i - 1];
    }
    
    arr[0] = arr[index];
}
