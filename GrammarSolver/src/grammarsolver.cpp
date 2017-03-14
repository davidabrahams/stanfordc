// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "grammarsolver.h"
using namespace std;


bool isTerminal(string &s) {
    if (s.length() < 2)
        return true;
    char f = s.front();
    char b = s.back();
    if (f == '<' and b == '>') return false;
    return true;
}

vector<string> translateToSymbols(string &symbol) {
    vector<string> res;
    return res;
}

vector<string> stringFromSymbol(string &symbol) {
    vector<string> res;
    if (isTerminal(symbol))
        res.push_back(symbol);
    else {
        for (string s : translateToSymbols(symbol)) {
            vector<string> v = stringFromSymbol(s);
            res.insert(res.end(), v.begin(), v.end());
        }
    }
    return res;
}

vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function
    
    vector<string> v;   // this is only here so it will compile
    return v;           // this is only here so it will compile
}
