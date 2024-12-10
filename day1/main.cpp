#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> parse_data(std::string& filename) {
    std::ifstream inputFile(filename);
    std::string line;
    std::vector<int> v;
    std::vector<std::vector<int>> v_out;
    while (std::getline(inputFile, line)) {
        std::string first = line.substr(0, line.find(' '));
        std::string second = line.substr(line.find(' ')+3, line.length());
        int first_int = std::stoi(first);
        int second_int = std::stoi(second);
        v.push_back(first_int);
        v.push_back(second_int);
        v_out.push_back(v);
        v.clear();
    }
    return v_out;
}

int part1(std::vector<std::vector<int>>& v_in) {
    std::vector<int> firsts;
    std::vector<int> seconds;
    for (int i=0; i<v_in.size(); ++i) {
        firsts.push_back(v_in[i][0]);
        seconds.push_back(v_in[i][1]);
    }
    std::sort(firsts.begin(), firsts.end());
    std::sort(seconds.begin(), seconds.end());

    int res = 0;
    for (int i=0; i< firsts.size(); ++i) {
        res += std::abs(firsts[i] - seconds[i]);
    }
    return res;
}

int part2(std::vector<std::vector<int>>& v_in) {
    std::vector<int> firsts;
    std::vector<int> seconds;
    for (int i=0; i<v_in.size(); ++i) {
        firsts.push_back(v_in[i][0]);
        seconds.push_back(v_in[i][1]);
    }
    int res = 0;
    for (int i=0; i<firsts.size(); ++i) {
        for (int j=0; j<seconds.size(); ++j) {
            if (firsts[i]==seconds[j]) {
                res += seconds[j];
            }
        }
    }
    return res;
}

int main() {
    std::vector<std::vector<int>> d = parse_data("data.txt");
    for (int i=0; i<d.size(); ++i) {
        std::cout << d[i][0] << ", " << d[i][1] << std::endl;
    }
    int res = part1(d);
    std::cout << res << std::endl;

    int res2 = part2(d);
    std::cout << res2 << std::endl;
}