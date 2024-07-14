#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void checkWinner(vector<string> blackHand, vector<string> whiteHand);
int checkHand(vector<string> hand);
int getValueOrder(string card);
bool sortFunction(string a, string b);

bool isStraight(vector<string> hand);
bool isFlush(vector<string> hand);

int main() {

    vector<string> blackHand;
    vector<string> whiteHand;
    string strInput = "";

    while (getline(cin, strInput)) {
        if (strInput.empty() || strInput.length() != 29) {
            break;
        }
        
        for (int i = 0; i < 10; i++) {
            string aux = strInput.substr(i * 3, 2);
            if (i < 5) {
                blackHand.push_back(aux);
            } else {
                whiteHand.push_back(aux);
            }
        }

        checkWinner(blackHand, whiteHand);
    }

    return 0;
}

void checkWinner(vector<string> blackHand, vector<string> whiteHand) {
    sort(blackHand.begin(), blackHand.end(), sortFunction);
    sort(whiteHand.begin(), whiteHand.end(), sortFunction);

    int blackOrder = checkHand(blackHand);
    int whiteOrder = checkHand(whiteHand);

    if (blackOrder > whiteOrder) {
        cout << "Black wins." << endl;
    } else if (blackOrder < whiteOrder) {
        cout << "White wins." << endl;
    } else {
        cout << "Tie." << endl;
    }

    return;
}

int checkHand(vector<string> hand) {
    
    bool is = isFlush(hand);
    for (auto h : hand) {
        cout << h << " ";
    }

    cout << endl << is << endl;

    return 0;
}

int getValueOrder(string card) {
    string value = card.substr(0, 1);

    if (value == "1") return 1;
    if (value == "2") return 2;
    if (value == "3") return 3;
    if (value == "4") return 4;
    if (value == "5") return 5;
    if (value == "6") return 6;
    if (value == "7") return 7;
    if (value == "8") return 8;
    if (value == "9") return 9;
    if (value == "T") return 10;
    if (value == "J") return 11;
    if (value == "Q") return 12;
    if (value == "K") return 13;
    if (value == "A") return 14;

    return 0;
}

bool sortFunction(string a, string b) {
    return getValueOrder(a) < getValueOrder(b);
}

bool isStraight(vector<string> hand) {
    int forth  = getValueOrder(hand[4]);
    int third  = getValueOrder(hand[3]);
    int second = getValueOrder(hand[2]);
    int first  = getValueOrder(hand[1]);
    int zero   = getValueOrder(hand[0]);

    cout << zero << " " << first << " " << second << " " <<third << " " <<forth << endl;

    if (    
        forth  == third  + 1 &&
        third  == second + 1 &&
        second == first  + 1 &&
        first  == zero   + 1
    ) return true;

    return false;
}

bool isFlush(vector<string> hand) {
    string forth  = hand[4].substr(1, 1);
    string third  = hand[3].substr(1, 1);
    string second = hand[2].substr(1, 1);
    string first  = hand[1].substr(1, 1);
    string zero   = hand[0].substr(1, 1);
    
    if (forth == third && third == second && second == first && first == zero) return true;

    return false;
}

