#include <iostream>
#include <vector>

using namespace std;

int golombSequence(int, vector<int>&);

int main() {
    int n;
    
    while (true) {
        cin >> n;
        if (n == 0) break;

        vector<int> memo(n+1, 0);

        cout << golombSequence(n, memo) << endl;
    }

    return 0;
}

int golombSequence(int n, vector<int>& memo) {
    if (n == 1) {
        return 1;
    } 

    if (memo[n] != 0) {
        return memo[n];
    }

    memo[n] = 1 + golombSequence(n - golombSequence(golombSequence(n-1, memo), memo), memo);
    
    return memo[n];
}
