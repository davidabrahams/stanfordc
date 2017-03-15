// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "grammarsolver.h"
#include "random.h"
#include "split.h"

void readFileIntoMap(istream &input, map<string, vector<vector<string>>> &m);

string stringFromSymbol(string &symbol, map<string, vector<vector<string>>> &grammar) {
    string res;
    if (! grammar.count(symbol))
        res = symbol;
    else {
        vector<vector<string>> randos = grammar[symbol];
        vector<string> chosen = randos.at(randomInteger(0, randos.size()-1));
        for (string c : chosen)
            res += stringFromSymbol(c, grammar) + ' ';
        res = res.substr(0, res.length()-1);
    }
    return res;
}

vector<string> grammarGenerate(istream& input, string symbol, int times, map<string, vector<vector<string>>> &grammar) {
    // TODO: write this function
    readFileIntoMap(input, grammar);
    vector<string> v;
    for (int i = 0; i < times; i++)
        v.push_back(stringFromSymbol(symbol, grammar));
    return v;           // this is only here so it will compile
}


void readFileIntoMap(istream &input, map<string, vector<vector<string>>> &m) {
    std::string line;
    while (std::getline(input, line))
    {
        std::size_t i = line.find("::=");
        string key = line.substr(0, i);
        string val = line.substr(i+3);
        vector<string> spl = split(val, '|');
        vector<vector<string>> res;
        for (string sp : spl) {
            vector<string> tmp = split(sp, ' ');
            res.push_back(tmp);
        }
        m[key] = res;
    }
//    cout << m.toString() << endl;
}
