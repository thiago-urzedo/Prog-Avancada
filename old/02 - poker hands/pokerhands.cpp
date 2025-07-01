/*
Comando usado para compilar:
$ g++ pokerhands.cpp -o pokerhands.out -Wall

Entrada:
2H 3D 5S 9C KD 2C 3H 4S 8C AH
2H 4S 4C 2D 4H 2S 8S AS QS 3S
2H 3D 5S 9C KD 2C 3H 4S 8C KH
2H 3D 5S 9C KD 2D 3H 5C 9S KH

* A resposta é dada a cada iteração
*/
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
bool isFourOAK(vector<string> hand);
bool isFullHouse(vector<string> hand);
bool isThreeOAK(vector<string> hand);
bool isPair(vector<string> hand);
bool isTwoPairs(vector<string> hand);

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
        
        blackHand.erase(blackHand.begin(), blackHand.end());
        whiteHand.erase(whiteHand.begin(), whiteHand.end());
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
    
    if (isStraight(hand) && isFlush(hand)) return 90;
    if (isFourOAK(hand)) return 80;
    if (isFullHouse(hand)) return 70;
    if (isFlush(hand)) return 60;
    if (isStraight(hand)) return 50;
    if (isThreeOAK(hand)) return 40;
    if (isTwoPairs(hand)) return 30;
    if (isPair(hand)) return 20;

    return getValueOrder(hand[4]);
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

    if (forth == (third + 1) && third == (second + 1) && second == (first + 1) && first == (zero + 1) ) return true;

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

bool isFourOAK(vector<string> hand) {
    int forth  = getValueOrder(hand[4]);
    int first  = getValueOrder(hand[1]);
    int zero   = getValueOrder(hand[0]);

    if (zero == first || first == forth) return true;

    return false;
}

bool isFullHouse(vector<string> hand) {
    return isThreeOAK(hand) && isPair(hand);
}

bool isThreeOAK(vector<string> hand) {
    int forth  = getValueOrder(hand[4]);
    int second = getValueOrder(hand[2]);
    int zero   = getValueOrder(hand[0]);

    if (zero == second || second == forth) return true;

    return false;
}

bool isPair(vector<string> hand) {
    int forth  = getValueOrder(hand[4]);
    int third  = getValueOrder(hand[3]);
    int second = getValueOrder(hand[2]);
    int first  = getValueOrder(hand[1]);
    int zero   = getValueOrder(hand[0]);

    if (zero == first || first == second || second == third || third == forth) return true;

    return false;
}

bool isTwoPairs(vector<string> hand) {
    int pairCount = 0;
    int forth  = getValueOrder(hand[4]);
    int third  = getValueOrder(hand[3]);
    int second = getValueOrder(hand[2]);
    int first  = getValueOrder(hand[1]);
    int zero   = getValueOrder(hand[0]);

    if (zero == first) pairCount++;
    if (first == second) pairCount++;
    if (second == third) pairCount++;
    if (third == forth) pairCount++;

    return pairCount > 1;
}
