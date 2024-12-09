#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <utility>
#include <set>

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

class Guard {
public: 
    int row;
    int col;
    char dir = 'n';
    vector<pair<int, int>> visited;
    Guard(int row, int col) : row(row), col(col) {};
    void logPosition(int row, int col) {
        visited.push_back({row, col});
    }
    void turn() {
        switch (dir) {
            case 'n' :
                dir = 'e';
                break;
            case 'e' :
                dir = 's';
                break;
            case 's' : 
                dir = 'w';
                break;
            case 'w' : 
                dir = 'n';
                break;
        }
    }
    void step() {
        switch (dir) {
            case 'n' :
                row -= 1;
                break;
            case 'e' :
                col += 1;
                break;
            case 's' : 
                row += 1;
                break;
            case 'w' : 
                col -= 1;
                break;
        }
    }
};

Guard findStart(vector<vector<char>> grid) {
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[i].size(); ++j) {
            if (grid[i][j]=='^') {
                return Guard(i, j);
            }
        }
    }
}

char getNext(vector<vector<char>> grid, Guard currentLoc) {
    try {
        switch (currentLoc.dir) {
            case 'n':
                return grid.at(currentLoc.row-1).at(currentLoc.col);
            case 'e':
                return grid.at(currentLoc.row).at(currentLoc.col+1);
            case 's' :
                return grid.at(currentLoc.row+1).at(currentLoc.col);
            case 'w':
                return grid.at(currentLoc.row).at(currentLoc.col-1);
        }
    } catch (const out_of_range& e) {
        return 'f';
    }
}


int part1(vector<vector<char>> grid) {
    Guard guard = findStart(grid);
    char next = getNext(grid, guard);
    while (next != 'f') {
        // cout << "Guard pos: " << guard.row << ", " << guard.col << endl;
        guard.logPosition(guard.row, guard.col);
        if (next != '#') {
            guard.step();
        } else {
            guard.turn();
            guard.step();
        }
        next = getNext(grid, guard);
    }
    // return s;
    set<pair<int, int>> unique_pairs(guard.visited.begin(), guard.visited.end());
    return unique_pairs.size()+1; // Not sure why off-by-one
}

int part2(vector<vector<char>> grid) {
    // Guard guard = findStart(grid);
    int n = 0;
    for (int row=0; row<grid.size(); ++row) {
        for (int col=0; col<grid[0].size(); ++col) {
            Guard guard = findStart(grid);
            if (row==guard.row && col==guard.col) {
                continue;
            }
            // Place blockade:
            char was = grid[row][col];
            grid[row][col] = '#';
            cout << "Blockade at: " << row << ", " << col << endl;
            bool inLoop = false;
            // Start moving guard
            char next = getNext(grid, guard);
            // cout << next << endl;
            while (next!='f') {
                // cout << guard.row << ", " << guard.col << endl;
                guard.logPosition(guard.row, guard.col);
                if (next != '#') {
                    guard.step();
                } else {
                    guard.turn();
                    guard.step();
                }
                next = getNext(grid, guard);
                // Check num times visited point if have visited 
                int n_times_visit = count(guard.visited.begin(), guard.visited.end(), pair{guard.row, guard.col});
                // cout << n_times_visit << endl;
                if (n_times_visit>4) {
                    inLoop = true;
                    break;
                }
            }
            if (inLoop) {
                n+=1;
            }
            // Reset blockade: 
            grid[row][col] = was;
        }
    }
    return n;
}

int main() {
    vector<vector<char>> grid = parse_data("data.txt");
    // int res1 = part1(grid);
    // cout << res1 << endl;
    cout << part2(grid) << endl;
}