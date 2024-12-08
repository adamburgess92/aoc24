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

multimap<int, int> parse_rules(vector<string> vs) {
    multimap<int, int> map_out; 
    for (int i=0; i<vs.size(); ++i) {
        string left = vs[i].substr(0, vs[i].find('|'));
        string right = vs[i].substr(vs[i].find('|')+1);
        int left_int = stoi(left);
        int right_int = stoi(right);
        map_out.insert(pair{left_int, right_int});
    }
    return map_out;

}

int get_middle_number(vector<int> v_in) {
    int l = v_in.size();
    return v_in[l/2];
}

void part1(vector<vector<int>> updates, multimap<int, int> rules) {
    vector<vector<int>> correctly_ordered_updates;
    for (int i=0; i<updates.size(); ++i) {
        bool all_ok = true;
        for (int j=0; j<updates[i].size(); ++j) {
            bool order_correct = true;
            vector<int> before(updates[i].begin(), updates[i].begin()+j);
            vector<int> after(updates[i].begin()+j+1, updates[i].end());
            int target = updates[i][j];
            cout << "target: " << target << endl;
            // Get rules before
            vector<int> before_rules; 
            vector<int> after_rules;
            for (const auto& [k, v] : rules) {
                if (v==target) {
                    before_rules.push_back(k);
                }
                if (k==target) {
                    after_rules.push_back(v);
                }
            }
            // Ensure that everything in 'before' appears int 'before_rules': 
            bool before_ok = true;
            if (before.size()>0) {
                before_ok = all_of(before.begin(), before.end(), [&](int e) {
                    return find(before_rules.begin(), before_rules.end(), e) != before_rules.end();
                });
            }
            // And again for 'after'
            bool after_ok = true;
            if (after.size()>0) {
                after_ok = all_of(after.begin(), after.end(), [&](int e) {
                    return find(after_rules.begin(), after_rules.end(), e) != after_rules.end();
                });
            }
            if (!before_ok || !after_ok) {
                all_ok = false;
            }
        }
        if (all_ok) {
            correctly_ordered_updates.push_back(updates[i]);
        }
        cout << endl;
    }
    int s = 0;
    for (int i=0; i<correctly_ordered_updates.size(); ++i) {
        int middle_number = get_middle_number(correctly_ordered_updates[i]);
        cout << middle_number << endl;
        s += middle_number;
    }
    return s;
}

int main() {
    vector<string> update_data = parse_data("test_update.txt");
    vector<vector<int>> updates = parse_updates(update_data);

    vector<string> rule_data = parse_data("test_rules.txt");
    multimap<int, int> rules = parse_rules(rule_data);

    part1(updates, rules);
}
