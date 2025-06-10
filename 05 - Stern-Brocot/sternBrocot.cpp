// Ref: https://github.com/KHvic/uva-online-judge/blob/master/10077-The%20Stern-Brocot%20Number%20System.cpp

#include <iostream>
#include <utility>

using namespace std;

int main() {
    int m, n;
    pair<int,int> left,right,mid;

    cin >> n >> m;

    while (!(n == 1 && m == 1)) {
        
        string out = "";
        left = {0,1}, right = {1,0}, mid = {1,1};

        while (mid.first != n || mid.second != m) {
            // avoid floating point calc
            int v1 = n*mid.second;
            int v2 = m*mid.first;

            if (v1<v2) { // go left
                right = mid;
                mid = {left.first+mid.first, left.second+mid.second};
                out += 'L';
            } else { // go right
                left = mid;
                mid = {mid.first+right.first, mid.second+right.second};
                out += 'R';
            }
        }

        cout << out << endl;
        cin >> n >> m;
    }

    return 0;
}
