#include <string>
#include <iostream> 
#include <vector> 
#include <fstream> 
#include <sstream>
#include <tuple>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

vector<string> parse_data(const string& filename) {
    ifstream input_file(filename);
    string line;
    vector<string> out;
    while (getline(input_file, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' ')) {
            out.push_back(token);
        }
    }
    return out;
}

bool is_zero(const string& s) {
    if (s == "0") {
        return true;
    }
    return false;
}

bool even_digits(const string& s) {
    if (s.length()%2==0) {
        return true;
    }
    return false;
}

string strip_leading_zeros(const string& s) {
    string out = "";
    for (char c : s) {
        if (out.length()==0 && c=='0') {
            continue;
        }
        out.push_back(c);
    }
    if (out.length()==0) {
        return "0";
    }
    return out;
}

tuple<string, string> split_stone(const string& s) {
    int n = s.length(); 
    string first = s.substr(0, n/2);
    string second = s.substr(n/2, s.length());
    first = strip_leading_zeros(first);
    second = strip_leading_zeros(second);
    return make_tuple(first, second);
}

string multiply2024(const string s) {
    int128_t bigInt;
    bigInt = int128_t(s)*2024;
    return bigInt.str();
}

int sum_stones(vector<string>& stones) {
    int r = 0;
    for (string s: stones) {
        int val = stoi(s);
        r += val;
    }
    return r;
}

int part1(int n_blinks, vector<string>& input) { 
    // Copy: 
    vector<string> stones = input;
    int c = 1;
    while (c <= n_blinks) {
        vector<string> updated_stones;
        for (int i=0; i<stones.size(); ++i) {
            // cout << stones[i] << endl;
            // Rule 1: 
            if (is_zero(stones[i])) {
                updated_stones.push_back("1");
            } else if (even_digits(stones[i])) {
                tuple<string, string> two_stones = split_stone(stones[i]);
                updated_stones.push_back(get<0>(two_stones));
                updated_stones.push_back(get<1>(two_stones));
            } else {
                string multiplied = multiply2024(stones[i]);
                updated_stones.push_back(multiplied);
            }
        }


        stones = updated_stones;
        // cout << "After " << c << " blinks"  << endl;
        // for (int i=0; i<stones.size(); ++i) {
        //     cout << stones[i] << " ";
        // }
        // cout << endl;
        ++c;
        cout << c << endl;
    }
    // return sum_stones(stones);
    return stones.size();
}

int main() {
    vector<string> d = parse_data("data.txt");
    for (auto s : d) {
        cout << s << endl;
    }
    cout << endl;
    int res = part1(75, d);
    cout << res << endl;
}