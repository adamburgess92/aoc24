#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>

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

vector<Coord> findX(vector<vector<char>> d) {
    vector<Coord> v_out;
    for (int row=0; row<d.size(); ++row) {
        for (int col=0; col<d[0].size(); ++col) {
            if (d[row][col]=='X') {
                Coord c(row, col);
                v_out.push_back(c);
            }
        }
    }
    return v_out;
}

int north(Coord c, vector<vector<char>> grid) {
    if (c.row<3) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row-1][c.col]=='M' && grid[c.row-2][c.col]=='A' && grid[c.row-3][c.col]=='S') {
        return 1;
    }
    return 0;
}

int north_east(Coord c, vector<vector<char>> grid) {
    if (c.row<3 || c.col>grid[0].size()-4) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row-1][c.col+1]=='M' && grid[c.row-2][c.col+2]=='A' && grid[c.row-3][c.col+3]=='S') {
        return 1;
    }
    return 0;
}

int east(Coord c, vector<vector<char>> grid) {
    if (c.col>grid[0].size()-4) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row][c.col+1]=='M' && grid[c.row][c.col+2]=='A' && grid[c.row][c.col+3]=='S') {
        return 1;
    }
    return 0;
}

int south_east(Coord c, vector<vector<char>> grid) {
    if (c.row>grid.size()-4 || c.col>grid[0].size()-4) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row+1][c.col+1]=='M' && grid[c.row+2][c.col+2]=='A' && grid[c.row+3][c.col+3]=='S') {
        return 1;
    }
    return 0;
}

int south(Coord c, vector<vector<char>> grid) {
    if (c.row>grid.size()-4) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row+1][c.col]=='M' && grid[c.row+2][c.col]=='A' && grid[c.row+3][c.col]=='S') {
        return 1;
    }
    return 0;
}

int south_west(Coord c, vector<vector<char>> grid) {
    if (c.row>grid.size()-4 || c.col<3) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row+1][c.col-1]=='M' && grid[c.row+2][c.col-2]=='A' && grid[c.row+3][c.col-3]=='S') {
        return 1;
    }
    return 0;
}

int west(Coord c, vector<vector<char>> grid) {
    if (c.col<3) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row][c.col-1]=='M' && grid[c.row][c.col-2]=='A' && grid[c.row][c.col-3]=='S') {
        return 1;
    }
    return 0;
}

int north_west(Coord c, vector<vector<char>> grid) {
    if (c.row < 3 || c.col<3) {
        return 0;
    }
    if (grid[c.row][c.col]=='X' && grid[c.row-1][c.col-1]=='M' && grid[c.row-2][c.col-2]=='A' && grid[c.row-3][c.col-3]=='S') {
        return 1;
    }
    return 0;
}

int part1(vector<vector<char>> grid) { 
    vector<Coord> xs = findX(grid);
    int s = 0;
    for (Coord c : xs) {
        s += (
            north(c, grid) +
            north_east(c, grid) +
            east(c, grid) +
            south_east(c, grid) +
            south(c, grid) +
            south_west(c, grid) +
            west(c, grid) +
            north_west(c, grid)
        );
    }
    return s;
}

int main() {
    vector<vector<char>> d = parse_data("data.txt");
    cout << part1(d) << endl;
}