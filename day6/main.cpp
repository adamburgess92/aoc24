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

vector<tuple<int, int>> getPath(vector<vector<char>> grid) {
    int min_i = 0;
    int min_j = 0;
    int max_i = grid.size()-1;
    int max_j = grid[0].size()-1;

    // Find start:
    int init_i;
    int init_j;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == '^') {
                init_i = i;
                init_j = j;
            }
        }
    }

    // Init stuff
    int curr_i = init_i;
    int curr_j = init_j;
    bool inbounds = true;
    map<char, tuple<int,int>> d_map{{'n', tuple(-1, 0)}, {'e', tuple(0, 1)}, {'s', tuple(1, 0)}, {'w', tuple(0, -1)}};
    char d = 'n';

    // Keep a log of visited locations:
    vector<tuple<int, int>> v;

    while (inbounds) {
        v.push_back(make_tuple(curr_i, curr_j));
        int dx = get<0>(d_map[d]);
        int dy = get<1>(d_map[d]);
        if (curr_i+dx>max_i || curr_j+dy>max_j || curr_i+dx<0 || curr_j+dy<0) {
            inbounds = false;
            break;
        }
        char next_c = grid[curr_i+dx][curr_j+dy];
        if (next_c == '#') {
            switch (d) {
                case 'n' :
                    d = 'e';
                    break;
                case 'e' :
                    d = 's';
                    break;
                case 's' :
                    d = 'w';
                    break;
                case 'w' :
                    d = 'n';
                    break;
            }
            continue;
        }
        curr_i += dx;
        curr_j += dy;
    }
    return v;
}

int part1(vector<vector<char>> grid) {
    vector<tuple<int, int>> p = getPath(grid);
    // for (tuple<int, int> t : p) {
    //     cout << get<0>(t) << ", " << get<1>(t) << endl;
    // }
    return set(p.begin(), p.end()).size();
}

int part2(vector<vector<char>> grid) {
    int min_i = 0;
    int min_j = 0;
    int max_i = grid.size()-1;
    int max_j = grid[0].size()-1;
    // Get guard path
    vector<tuple<int, int>> path = getPath(grid);
    set<tuple<int, int>> u_path(path.begin(), path.end());
    int n=0;
    int n_total = u_path.size();
    // Find start:
    int init_i;
    int init_j;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == '^') {
                init_i = i;
                init_j = j;
            }
        }
    }
    for (tuple<int, int> point : u_path) {
        int r = get<0>(point);
        int c = get<1>(point);
        if (r==init_i && c==init_j) {
            continue;
        }
        // Pretty much do the same thing as part 1 again, with a blockade...
        int curr_i = init_i;
        int curr_j = init_j;
        bool inbounds = true;
        map<char, tuple<int,int>> d_map{{'n', tuple(-1, 0)}, {'e', tuple(0, 1)}, {'s', tuple(1, 0)}, {'w', tuple(0, -1)}};
        char d = 'n';
        // Keep a log of visited locations:
        vector<tuple<int, int>> v;
        // Loop
        while (inbounds) {
            tuple<int, int> curr_tpl = make_tuple(curr_i, curr_j);
            v.push_back(curr_tpl);
            int dx = get<0>(d_map[d]);
            int dy = get<1>(d_map[d]);
            if (curr_i+dx>max_i || curr_j+dy>max_j || curr_i+dx<0 || curr_j+dy<0) {
                inbounds = false;
                break;
            }
            char next_c = grid[curr_i+dx][curr_j+dy];
            if (next_c == '#' || (curr_i+dx==r && curr_j+dy==c)) {
                switch (d) {
                    case 'n' :
                        d = 'e';
                        break;
                    case 'e' :
                        d = 's';
                        break;
                    case 's' :
                        d = 'w';
                        break;
                    case 'w' :
                        d = 'n';
                        break;
                }
                continue;
            }
            if (v.size()>10000) {
                n +=1;
                inbounds = false; // to break out of outer loop
                cout << curr_i << ", " << curr_j << " | " << n << "/" << n_total << endl;
                break;
            }
            curr_i += dx;
            curr_j += dy;
        }
    }
    return n;
}

int main() {
    vector<vector<char>> d = parse_data("data.txt");
    int res1 = part1(d);
    cout << res1 << endl;

    int res2 = part2(d);
    cout << res2 << endl;
}