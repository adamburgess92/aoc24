#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

vector<string> parse_data(const string& filename) {
    ifstream inputFile(filename);
    string line;
    vector<string> v_out;
    while (getline(inputFile, line)) {
        v_out.push_back(line);
    }
    return v_out;
}

int part1(vector<string>& d) {
    // Build vector of strings ["mul(123,456)", "mul(93,83)", ...]
    vector<string> vec_mul;
    for (int i=0; i<d.size(); ++i) {
        string s = d[i];
        // Regex things
        regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
        smatch res;

        sregex_iterator rit(s.begin(), s.end(), pattern);
        sregex_iterator rend;

        for (sregex_iterator i=rit; i!=rend; ++i) {
            smatch match = *i;
            vec_mul.push_back(match.str());
        }
    }
    // Iterate over everything in ["mul(123,456)", "mul(93,83)", ...],
    // extract ints and multiply
    int s = 0;
    for (int i=0; i<vec_mul.size(); ++i) {
        string a_str = vec_mul[i].substr(vec_mul[i].find('(')+1, vec_mul[i].find(',')-vec_mul[i].find('(')-1);
        string b_str = vec_mul[i].substr(vec_mul[i].find(',')+1, vec_mul[i].find(')')-vec_mul[i].find(',')-1);
        int a = stoi(a_str);
        int b = stoi(b_str);
        s += (a*b);
    }
    return s;
}

// Part 2:
// Chop out parts of data between do() and don't() pushing results
// to a vector<str>
// For each element in vector<str> call part1 on it.
void part2(vector<string>& d) {
    // Build string, because currently it's split by line
    string s;
    vector<string> v;
    for (int i=0; i<d.size(); ++i) {
        s += d[i];
    }
    // Now we have a single string...
    string do_str = "do()";
    string dont_str = "don't()";
    int s_len = s.length();

    // For first iter:
    int do_idx = 0;
    while (do_idx<s_len) {
        int dont_idx = s.find(dont_str, do_idx);
        string substr = s.substr(do_idx, dont_idx-do_idx);
        cout << substr << endl;
        v.push_back(substr);
        s = s.substr(dont_idx, s.length()-1);
        do_idx = s.find(do_str, dont_idx);
        cout << do_idx << endl;
    }
    cout << part1(v) << endl;

}


int main() {
    vector<string> d = parse_data("test_data.txt");
    // part1(d);
    part2(d);
}