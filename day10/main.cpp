#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <queue> 
#include <tuple>
#include <map>

using namespace std;

vector<vector<int>> parse_data(const string& filename) {
    ifstream inputFile(filename);
    string line;
    vector<vector<int>> v_out;
    while (getline(inputFile, line)) {
        vector<int> v;
        for (int i=0; i<line.length(); ++i) {
            int n = line[i] - '0';
            v.push_back(n);
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
};

vector<Point> get_starts(vector<vector<int>>& grid) {
    vector<Point> v_out;
    for (int row=0; row<grid.size(); ++row) {
        for (int col=0; col<grid[0].size(); ++col) {
            if (grid[row][col]==0) {
                Point p(row, col);
                v_out.push_back(p);
            }
        }
    }
    return v_out;
}

bool already_visited(Point p, queue<Point> q) {
    while (!q.empty()) {
        Point c = q.front();
        q.pop();
        if (c.row==p.row && c.col==p.col) {
            return true;
        }
    }
    return false;
}

int get_score(Point p, vector<vector<int>>& grid) {
    cout << "Start point: " << p.row << ", " << p.col << endl;
    int min_r = 0;
    int max_r = grid.size()-1;
    int min_c = 0;
    int max_c = grid[0].size()-1;

    vector<Point> peaks;

    queue<Point> q;
    queue<Point> visited;
    q.push(p);

    map<char, tuple<int,int>> d_map{{'n', make_tuple(-1, 0)}, {'e', make_tuple(0, 1)}, {'s', make_tuple(1, 0)}, {'w', make_tuple(0, -1)}};

    while (q.size()>0) {
        Point curr = q.front();
        q.pop();
        // Part 1 - uncomment this block: 
        // if (already_visited(curr, visited)) {
        //     continue;
        // }
        visited.push(curr);
        int curr_row = curr.row;
        int curr_col = curr.col;
        int curr_val = grid[curr_row][curr_col];

        if (curr_val == 9) {
            peaks.push_back(curr);
            continue;
        }

        // Get surrounds: 
        for (auto [k, v] : d_map) {
            // Check in bounds:
            if (curr_row+get<0>(v)<min_r || curr_row+get<0>(v)>max_r || curr_col+get<1>(v)<min_c || curr_col+get<1>(v)>max_c) {
                continue;
            }
            int step_val = grid[curr_row+get<0>(v)][curr_col+get<1>(v)];
            if (step_val - curr_val == 1) {
                Point potential_p = Point(curr_row+get<0>(v), curr_col+get<1>(v));
                q.push(potential_p);
            }
        }
    }

    cout << "Peaks at " << endl;
    for (auto p : peaks) {
        cout << p.row << ", " << p.col << endl;
    }
    return peaks.size();
}

int part1(vector<vector<int>>& grid) {
    vector<Point> start_points = get_starts(grid);
    int res = 0;
    for (Point p : start_points) {
        res += get_score(p, grid);
    }
    return res;
}

int main() {
    vector<vector<int>> d = parse_data("data.txt");
    int res = part1(d);
    cout << res << endl;
}