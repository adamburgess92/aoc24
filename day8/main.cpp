#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <utility>
#include <set>
#include <map>

using namespace std;

class Point {
public:
    int row;
    int col;
    Point(int row, int col) : row(row), col(col) {};
};

vector<string> parse_data(const string& filename) {
    ifstream inputFile(filename);
    string line;
    vector<string> v_out;
    while (getline(inputFile, line)) {
        v_out.push_back(line);
    }
    return v_out;
}

map<char, vector<Point>> get_points(vector<string>& grid) {
    map<char, vector<Point>> m;
    for (int row=0; row<grid.size(); ++row) {
        for (int col=0; col<grid[row].size(); ++col) {
            char c = grid[row][col];
            if (c!='.') {
                // If key doesn't exist yet:
                bool key_exists = false;
                for (auto [key, val] : m) {
                    if (key==c) {
                        key_exists = true;
                    }
                }
                if (!key_exists) {
                    Point new_point = Point(row, col);
                    m[c] = vector{new_point};
                } else {
                    m[c].push_back(Point(row, col));
                }
            }
        }
    }
    return m;
}

void part1(vector<string> grid) {
    map<char, vector<Point>> points_map = get_points(grid);
    for (auto [k, v] : points_map) {
        cout << k << endl;
        for (Point p: v) {
            cout << p.row << ", " << p.col << endl;
        }
    }
}

int main() {
    vector<string> d = parse_data("data.txt");
    for (const string& s : d) {
        cout << s << endl;
    }
    cout << endl;
    part1(d);
}