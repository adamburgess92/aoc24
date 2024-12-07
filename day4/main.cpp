#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;

vector<vector<char>> parse_data(const string& filename) {
    ifstream inputFile(filename);
    string line;
    vector<vector<char>> v_out; 
    while (getline(inputFile, line)) {
        vector<char> v;
        for (int i=0; i<line.length(); ++i) {
            v.push_back(line[i]);
        }
        v_out.push_back(v);
        v.clear();
    }
    return v_out;
}

class Coord {
public: 
    int row;
    int col;
    Coord(int row, int col) : row(row), col(col) {};
};

vector<Coord> findChar(vector<vector<char>> d, char ch) {
    vector<Coord> v_out;
    for (int row=0; row<d.size(); ++row) {
        for (int col=0; col<d[0].size(); ++col) {
            if (d[row][col]==ch) {
                Coord c(row, col);
                v_out.push_back(c);
            }
        }
    }
    return v_out;
}

bool n(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row-1).at(c.col)=='M' && grid.at(c.row-2).at(c.col)=='A' && grid.at(c.row-3).at(c.col)=='S';
}
bool ne(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row-1).at(c.col+1)=='M' && grid.at(c.row-2).at(c.col+2)=='A' && grid.at(c.row-3).at(c.col+3)=='S';
}
bool e(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row).at(c.col+1)=='M' && grid.at(c.row).at(c.col+2)=='A' && grid.at(c.row).at(c.col+3)=='S';
}
bool se(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row+1).at(c.col+1)=='M' && grid.at(c.row+2).at(c.col+2)=='A' && grid.at(c.row+3).at(c.col+3)=='S';
}
bool s(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row+1).at(c.col)=='M' && grid.at(c.row+2).at(c.col)=='A' && grid.at(c.row+3).at(c.col)=='S';
}
bool sw(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row+1).at(c.col-1)=='M' && grid.at(c.row+2).at(c.col-2)=='A' && grid.at(c.row+3).at(c.col-3)=='S';
}
bool w(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row).at(c.col-1)=='M' && grid.at(c.row).at(c.col-2)=='A' && grid.at(c.row).at(c.col-3)=='S';
}
bool nw(Coord c, vector<vector<char>> grid) {
    return grid.at(c.row).at(c.col)=='X' && grid.at(c.row-1).at(c.col-1)=='M' && grid.at(c.row-2).at(c.col-2)=='A' && grid.at(c.row-3).at(c.col-3)=='S';
}
int checkDir(Coord c, vector<vector<char>> grid, function<bool(Coord, vector<vector<char>>)> f) {
    try {
        if (f(c, grid)) {
            return 1;
        }
    } catch (const out_of_range& e) {
        return 0;
    }
    return 0;
}

int part1(vector<vector<char>> grid) { 
    vector<Coord> xs = findChar(grid, 'X');
    int count = 0;
    for (Coord c : xs) {
        count += (
            checkDir(c, grid, n) +
            checkDir(c, grid, ne) +
            checkDir(c, grid, e) +
            checkDir(c, grid, se) +
            checkDir(c, grid, s) +
            checkDir(c, grid, sw) +
            checkDir(c, grid, w) +
            checkDir(c, grid, nw)
        );
    }
    return count;
}

int checkCross(Coord c, vector<vector<char>> grid) {
    vector<char> x;
    char ne = '\0', se = '\0', sw = '\0', nw = '\0';
    try {
        ne = grid.at(c.row - 1).at(c.col + 1);
        x.push_back(ne);
    } catch (const out_of_range& e) {
        return 0;
    }
    try {
        se = grid.at(c.row + 1).at(c.col + 1);
        x.push_back(se);
    } catch (const out_of_range& e) {
        return 0;
    }
    try {
        sw = grid.at(c.row + 1).at(c.col - 1);
        x.push_back(sw);
    } catch (const out_of_range& e) {
        return 0;
    }
    try {
        nw = grid.at(c.row - 1).at(c.col - 1);
        x.push_back(nw);
    } catch (const out_of_range& e) {
        return 0;
    }

    // Check diagonal - if they match, it's invalid
    if (ne == sw || nw == se) {
        return 0;
    }

    // Check for 2x 'M' and 2x 'S'
    int n_S = count(x.begin(), x.end(), 'S');
    int n_M = count(x.begin(), x.end(), 'M');
    if (n_S == 2 && n_M == 2) {
        return 1;
    }
    return 0;
}

int part2(vector<vector<char>> grid) {
    vector<Coord> as = findChar(grid, 'A');
    int count = 0;
    for (Coord c : as) {
        count += checkCross(c, grid);
    }
    return count;
}

int main() {
    vector<vector<char>> d = parse_data("data.txt");
    cout << part1(d) << endl;
    cout << part2(d) << endl;
}
