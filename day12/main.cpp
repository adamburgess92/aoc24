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
#include <tuple>
#include <queue>

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
class Point {
public: 
    int row;
    int col;
    Point(int row, int col) : row(row), col(col) {};
    bool operator==(const Point& other) const {
        return (row==other.row) && (col==other.col);
    }
    bool operator<(const Point& other) const { 
        return (row < other.row) || (row==other.row && col<other.col);
    }
};

bool queue_contains_point(queue<Point> q, Point p) {
    while (!q.empty()) {
        Point i = q.front();
        q.pop();
        if (i==p) {
            return true;
        }

    }
    return false;
}

int part1(vector<vector<char>>& grid) {
    // Helpful vars
    int min_r = 0;
    int max_r = grid.size()-1;
    int min_c = 0;
    int max_c = grid[0].size()-1;
    // Return value: 
    int res = 0;
    // Vector of already-seen points:
    vector<Point> seen;

    for (int r=min_r; r<=max_r; ++r) {
        for (int c=min_c; c<=max_c; ++c) {
            int cost = 0;
            // Do BFS from root
            // Skip root if we've already been to this point.
            bool seen_already = false;
            for (Point p : seen) {
                if (p.row==r && p.col==c) {
                    seen_already = true;
                }
            }
            if (seen_already) {
                continue;
            }
            // BFS: 
            Point root = Point(r, c);
            // cout << "Root " << root.row << ", " << root.col << "~~~~~~~~~~~~" << endl;
            queue<Point> q;
            queue<Point> v;
            q.push(root);
            // v.push(root);
            int perim=0;
            while (!q.empty()) {
                // cout << "Queue length: " << q.size() << endl;
                Point curr_p = q.front();
                q.pop();
                v.push(curr_p);
                seen.push_back(curr_p);
                int n_adj = 0;
                // Get neighbours: 
                if (curr_p.row-1 >= min_r) { // N
                    if (grid[curr_p.row][curr_p.col]==grid[curr_p.row-1][curr_p.col]) {
                        Point north = Point(curr_p.row-1, curr_p.col);
                        // if (v.find(north) == v.end()) {
                        if (!queue_contains_point(q, north) && !queue_contains_point(v, north)) {
                            q.push(north);
                            // cout << "North" << endl;
                        }
                        ++n_adj;
                    }
                }
                if (curr_p.row+1 <= max_r) { // S
                    if (grid[curr_p.row][curr_p.col]==grid[curr_p.row+1][curr_p.col]) {
                        Point south = Point(curr_p.row+1, curr_p.col);
                        // if (v.find(south) == v.end()) {
                        if (!queue_contains_point(q, south) && !queue_contains_point(v, south)) {
                            q.push(south);
                            // cout << "South" << endl;
                        }
                        ++n_adj;
                    }
                }
                if (curr_p.col-1 >= min_c) { // W
                    if (grid[curr_p.row][curr_p.col]==grid[curr_p.row][curr_p.col-1]) {
                        Point west = Point(curr_p.row, curr_p.col-1);
                        // if (v.find(west) == v.end()) {
                        if (!queue_contains_point(q, west) && !queue_contains_point(v, west)) {
                            q.push(west);
                            // cout << "West" << endl;
                        }
                        ++n_adj;
                    }
                }
                if (curr_p.col+1 <= max_c) { // E
                    if (grid[curr_p.row][curr_p.col]==grid[curr_p.row][curr_p.col+1]) {
                        Point east = Point(curr_p.row, curr_p.col+1);
                        // if (v.find(east) == v.end()) {
                        if (!queue_contains_point(q, east) && !queue_contains_point(v, east)) {
                            q.push(east);
                            // cout << "East" << endl;
                        }
                        ++n_adj;
                    }
                }
                // cout << "At: " << curr_p.row << ", " << curr_p.col << " perim: " << (4-n_adj) << endl;
                // cout << (4-n_adj) << endl;
                perim += (4-n_adj);
            }
            // cout << "area " << v.size() << endl;
            // cout << "perim " << perim << endl;
            cost = (v.size() * perim);
            // cout << "Cost " << cost << endl; 
            res += cost;
            // cout << "Res : " << res << endl;
        }
    }
    return res;
}

int main() {
    vector<vector<char>> grid = parse_data("data.txt");
    int res1 = part1(grid);
    cout << res1 << endl;
}

// Why is repeating vistes to some places?
// Need to chec that north/south/east/west not in queue either...
