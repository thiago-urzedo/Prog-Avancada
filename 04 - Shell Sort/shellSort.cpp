#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void moveTurtleToTop(vector<string>&, int);

int main() {
    int nTests, nTurtles;
    vector<string> original, desired, output;

    cin >> nTests;

    for (int i = 0; i < nTests; i++) {
        cin >> nTurtles;
        cin.ignore();
        
        int j;
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

        int k = nTurtles-1;
        string aux;
        while(k >= 0) {
            if (original[k].compare(desired[k]) == 0) {
                k--;
            } else {
                output.push_back(original[k]);
                moveTurtleToTop(original, k);
            }
        }

        for (int index = nTurtles - 1; index >= 0; index--) {
            if (find(output.begin(), output.end(), desired[index]) != output.end()) {
                cout << desired[index] << endl;
            }
        }

        cout << endl;
        original.clear();
        desired.clear();
        output.clear();
    }

    return 0;
}

void moveTurtleToTop(vector<string>& arr, int index) {
    string aux = arr[index];
    
    for (int i = index; i > 0; i--) {
        arr[i] = arr[i-1];
    }

    arr[0] = aux;
}
