#include <string>
#include "bogglegui.h"
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "shuffle.h"
#include "strlib.h"
using namespace std;

void placeCubes(const Vector<std::string>& letterCubes, Grid<char>& grid);
bool containsWords(const Grid<char>& board, Grid<bool>& visited, const string& word, int r, int c, int i);

Grid<char> generateRandomBoard(int size, const Vector<std::string>& letterCubes) {
    // TODO: write this function
    Grid<char> grid = Grid<char>(size, size);
    placeCubes(letterCubes, grid);
    shuffle(grid);
    return grid;       // this is only here so it will compile
}

bool humanWordSearch(const Grid<char>& board, const Lexicon& dictionary, const string& w) {
    string word = toUpperCase(w);
    if (!dictionary.contains(word)) return false;
    if (word.length() < BoggleGUI::MIN_WORD_LENGTH) return false;
    BoggleGUI::clearHighlighting();
    Grid<bool> visited = Grid<bool>(board.numRows(), board.numCols());
    cout << visited.toString2D() << endl;
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            if (containsWords(board, visited, word, r, c, 0)) {
                if (word.length() > 7) BoggleGUI::scorePointsHuman(11);
                else if (word.length() == 7) BoggleGUI::scorePointsHuman(5);
                else if (word.length() == 6) BoggleGUI::scorePointsHuman(3);
                else if (word.length() == 5) BoggleGUI::scorePointsHuman(2);
                else BoggleGUI::scorePointsHuman(1);
                return true;
            }
        }
    }
    return false;
}

Set<string> computerWordSearch(const Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords) {
    // TODO: write this function
    Set<string> todo;   // this is only here so it will compile
    return todo;        // this is only here so it will compile
}

void placeCubes(const Vector<std::string>& letterCubes, Grid<char>& grid) {
    int width = grid.numCols();
    for (int i = 0; i < letterCubes.size(); i++) {
        string s = letterCubes.get(i);
        char c = s.at(randomInteger(0, s.length()-1));
        grid[i/width][i%width] = c;
    }
}

bool containsWords(const Grid<char>& board, Grid<bool>& visited, const string& word, int r, int c, int i) {
    if (i==word.length()) return true;
    if (r==-1 || r==board.numRows()) return false;
    if (c==-1 || c==board.numCols()) return false;
    if (visited[r][c]) return false;
    BoggleGUI::setHighlighted(r, c, true);
    BoggleGUI::setAnimationDelay(50);
    if (board[r][c] != word[i]){
        BoggleGUI::setHighlighted(r, c, false);
        return false;
    }
    i++;
    visited[r][c] = true;
    if (containsWords(board, visited, word, r-1, c-1, i)) return true;
    if (containsWords(board, visited, word, r-1, c, i)) return true;
    if (containsWords(board, visited, word, r-1, c+1, i)) return true;
    if (containsWords(board, visited, word, r, c-1, i)) return true;
    if (containsWords(board, visited, word, r, c+1, i)) return true;
    if (containsWords(board, visited, word, r+1, c-1, i)) return true;
    if (containsWords(board, visited, word, r+1, c, i)) return true;
    if (containsWords(board, visited, word, r+1, c+1, i)) return true;
    visited[r][c] = false;
    BoggleGUI::setHighlighted(r, c, false);
    return false;
}
