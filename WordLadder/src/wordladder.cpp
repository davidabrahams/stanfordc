#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include <set>
#include <queue>
#include <stack>
using namespace std;


void readDictionary(set<string> &dic);
void wordLadder(string from, string to);


int main() {
    set<string> dictionary;
    readDictionary(dictionary);
    return 0;
}

void wordLadder(string from, string to) {
    queue<stack<string>> q;
    stack<string> stack;
    stack.push(to);
    q.push(stack);
    while (!q.empty()) {
    }
}

void readDictionary(set<string> &dic) {
    string fn = getLine("Enter the filename for your dictionary:");
    ifstream file;
    file.open(fn);
    string word;
    while (file >> word)
        dic.insert(word);
    cout << "Dictionary saved." << endl;
}
