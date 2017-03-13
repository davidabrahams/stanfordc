#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <list>
using namespace std;


void readDictionary(set<string> &dic);
list<string> wordLadder(string from, string to, set<string> &dictionary);
list<string> neighbors(string s, set<string> &dic, set<string> &visited);


int main() {
    set<string> dictionary;
    readDictionary(dictionary);
//    list<string> path = neighbors("dog", dictionary);
    string from = getLine("Enter first word");
    string to = getLine("Enter second word");
    list<string> ladder = wordLadder(to, from, dictionary);
    if (ladder.empty())
        cout << "No ladder found." << endl;
    else {
    cout << "A ladder from " + to + " back to " + from << endl;
    for (auto const& c : ladder)
        std::cout << c << ' ';
    }
    return 0;
}

list<string> wordLadder(string from, string to, set<string> &dictionary) {
    queue<list<string>> q;
    list<string> s;
    set<string> visited;
    s.push_front(to);
    visited.insert(to);
    q.push(s);
    while (!q.empty()) {
        list<string> st = q.front();
        q.pop();
        string word = st.front();
        for (string &u : neighbors(word, dictionary, visited)) {
            list<string> sta = st;
            sta.push_front(u);
            visited.insert(u);
            if (sta.front() == from)
                return sta;
            q.push(sta);
        }
    }
    return list<string>();
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

list<string> neighbors(string s, set<string> &dic, set<string> &visited) {
    list<string> lst;
    for (int i = 0; i<s.length(); i++) {
        for( char l = 'a'; l<='z'; l++) {
            string t = s;
            if (s.at(i) == l)
                continue;
            t.replace(i, 1, string(1, l));
            if (dic.count(t) && (!visited.count(t)))
                lst.push_back(t);
        }
    }
    return lst;
}
