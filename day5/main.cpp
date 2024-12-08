#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string> 
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <map>

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

vector<vector<int>> parse_updates(vector<string>& vs) {
    vector<vector<int>> v_out;
    for (int i=0; i<vs.size(); ++i) {
        vector<int> v;
        stringstream ss(vs[i]);
        string token;
        while (getline(ss, token, ',')) {
            v.push_back(stoi(token));
        }
        v_out.push_back(v);
    }
    return v_out;
}

multimap<int, int> parse_rules(vector<string>& vs) {
    multimap<int, int> map_out; 
    for (int i=0; i<vs.size(); ++i) {
        string left = vs[i].substr(vs[i].begin(), vs[i].find('|'));
        string right = vs[i].substr(vs[i].find('|'), vs[i].begin());
        int left_int = stoi(left);
        int right_int = stoi(right);
        multimap.insert(pair{left_int, right_int});
    }
    return map_out;

}

void part1(vector<vector<int>> updates) {
    for (int i=0; i<updates.size(); ++i) {
        for (int j=0; j<updates[i].size(); ++j) {
            vector<int> before(updates[i].begin(), updates[i].begin()+j);
            vector<int> after(updates[i].begin()+j, updates[i].end());
            int val = after[0];
            cout << before.size() << endl;
            cout << after.size() << endl;
        }
        cout << endl;
    }
}

int main() {
    vector<string> d = parse_data("test_data.txt");
    vector<vector<int>> updates = parse_updates(d);
    multimap<int, int> rules = parse_rules(d);
    // part1(updates);

}
