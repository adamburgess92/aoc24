#include <iostream> 
#include <vector> 
#include <algorithm>
#include <string>
#include <fstream> 
#include <sstream>

std::vector<std::vector<int>> parse_data(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::string line;
    std::vector<std::vector<int>> vec_out; 

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::vector<int> vec;
        int num;
        while (ss >> num) {
            vec.push_back(num);
        }
        vec_out.push_back(vec);
        vec.clear();
    }
    return vec_out;
}

bool increase_ok(std::vector<int>& v) {
    for (int i=1; i<v.size(); ++i) {
        int diff = std::abs(v[i] - v[i-1]);
        if (v[i] <= v[i-1] || diff>3) {
            return false;
        }
    }
    return true;
}
bool decrease_ok(std::vector<int>& v) {
    for (int i=1; i<v.size(); ++i) {
        int diff = std::abs(v[i] - v[i-1]);
        if (v[i] >= v[i-1] || diff>3) {
            return false;
        }
    }
    return true;
}
bool is_safe(std::vector<int>& v) {
    return (increase_ok(v) || decrease_ok(v));
}

int part1(std::vector<std::vector<int>>& d) {
    int out=0;
    for (int i=0; i<d.size(); ++i) {
        if (is_safe(d[i])) {
            out += 1;
        }
    }
    return out;
}

int part2(std::vector<std::vector<int>>& d) {
    int out = 0;
    for (int i=0; i<d.size(); ++i) {
        if (is_safe(d[i])) {
            out += 1;
            continue;
        } else {
            // create copy: 
            std::vector<int> v_copy = d[i];
            // Drop elements:
            for (int j=0; j<v_copy.size(); ++j) {
                v_copy.erase(v_copy.begin()+j);
                if (is_safe(v_copy)) {
                    out += 1;
                    break;
                } else {
                    v_copy = d[i];
                }
            }
        }
    }
    return out;
}

int main() {
    std::vector<std::vector<int>> d = parse_data("data.txt");
    int res1 = part1(d);
    std::cout << res1 << std::endl;
    int res2 = part2(d);
    std::cout << "part2: " << res2 << std::endl;
}