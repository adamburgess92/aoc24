#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

string load_data(const string& filename) {
    ifstream input_file(filename);
    string line;
    string out;
    while (getline(input_file, line)) {
        out = line;
    }
    return out;
}

vector<string> construct_line(const string& s) {
    int a = 0;
    vector<string> v_out;
    for (int i=0; i<s.length(); ++i) {
        int n = s[i] - '0';
        // cout << "n: " << n << endl;
        string to_push = ".";
        if (i%2==0) {
            to_push = to_string(a);
            ++a;
        }
        for (int j=0; j<n; ++j) {
            v_out.push_back(to_push);
        }
    }
    return v_out;
}

bool no_gaps_in_file_block(const vector<string>& v) {
    bool has_hit_gap_char = false; 
    bool hits_another_non_gap_char = false;
    for (string c : v) {
        if (!has_hit_gap_char && c==".") {
            has_hit_gap_char = true;
            continue;
        }
        if (has_hit_gap_char && c!=".") {
            hits_another_non_gap_char = true;
        }
        if (has_hit_gap_char && hits_another_non_gap_char) {
            return false;
        }
    }
    return true;
}

int get_idx_first_gap(vector<string>& v) {
    for (int i=0; i<v.size(); ++i) {
        if (v[i]==".") {
            return i;
        }
    }
    return v.size()-1;
}

int get_idx_last_char(vector<string>& v) {
    for (int i=v.size()-1; i>=0; --i) {
        if (v[i]!=".") {
            return i;
        }
    }
    return 0;
}

vector<string> update_line(vector<string> v) {
    vector<string> v_out = v;
    while (!no_gaps_in_file_block(v_out)) {
        int idx_gap = get_idx_first_gap(v_out);
        int idx_char = get_idx_last_char(v_out);
        v_out[idx_gap] = v_out[idx_char];
        v_out[idx_char] = '.';
    }
    return v_out;
}

boost::multiprecision::int128_t get_checksum(vector<string>& v) {
    boost::multiprecision::int128_t res = 0;
    for (int i=0; i<v.size(); ++i) {
        if (v[i]==".") {
            return res;
        }
        boost::multiprecision::int128_t val = boost::multiprecision::int128_t(v[i]);       
        boost::multiprecision::int128_t idx = boost::multiprecision::int128_t(i);
        cout << i << endl;
        // cout << v << endl;
        res += val * idx;
    }
    return res;
}

boost::multiprecision::int128_t part1(const string& s) {
    vector<string> line = construct_line(s);
    vector<string> adj_line = update_line(line);
    // for (string s : adj_line) {
    //     cout << s << endl;
    // }
    boost::multiprecision::int128_t checksum = get_checksum(adj_line);
    return checksum;
}

int main() {
    string input = load_data("test_data.txt");
    boost::multiprecision::int128_t res1 = part1(input);
    cout << res1 << endl;
}