#include <iostream> 
#include <fstream> 
#include <string> 
#include <map>
#include <vector> 

using namespace std;

vector<map<string, int>> parse_data(const string& filename) {
    ifstream input_file(filename);
    string line;
    vector<map<string, int>> v_out;
    map<string, int> m;
    int i = 1;
    while (getline(input_file, line)) { // Not amazing but it works... need to add newline to bottom of input file
        if (i%4==0) {
            v_out.push_back(m);
            m.clear();
            i = 1;
            continue;
        }
        if (i % 3 ==0) {
            string sp0 = line.substr(line.find('=')+1, line.find(',')-line.find('=')-1);
            string sp1 = line.substr(line.find(",")+4, line.length()-line.find(',')+3);
            int p0 = stoi(sp0);
            int p1 = stoi(sp1);
            m["p0"] = p0;
            m["p1"] = p1;
            ++i;
            continue;
        }
        if (i % 2 == 0) {
            string sb0 = line.substr(line.find('+')+1, line.find(',')-line.find('+')-1);
            string sb1 = line.substr(line.find(",")+4, line.length()-line.find(',')+3);
            int b0 = stoi(sb0);
            int b1 = stoi(sb1);
            m["b0"] = b0;
            m["b1"] = b1;
            ++i;
            continue;
        }
        else {
            string sa0 = line.substr(line.find('+')+1, line.find(',')-line.find('+')-1);
            string sa1 = line.substr(line.find(",")+4, line.length()-line.find(',')+3);
            int a0 = stoi(sa0);
            int a1 = stoi(sa1);
            m["a0"] = a0;
            m["a1"] = a1;
            ++i;
            continue;
        }
    }
    return v_out;
}

int part1(vector<map<string, int>>& vm) {
    int total_cost = 0;
    cout << vm.size() << endl;
    for (map<string, int> m : vm) {
        int cost = 0;
        int p0 = m["p0"];
        int p1 = m["p1"];
        int a0 = m["a0"];
        int a1 = m["a1"];
        int b0 = m["b0"];
        int b1 = m["b1"];

        for (int alpha=0; alpha<100; ++alpha) {
            cout << alpha << endl;
            for (int beta=0; beta<=100; ++beta) {
                if (p0==alpha*a0 + beta*b0 && p1==alpha*a1 + beta*b1) {
                    cost = 3*alpha + beta;
                    if (3*alpha+beta > 0 && 3*alpha+beta < cost) { // wot
                        cost = 3*alpha+beta;
                    }
                }
            }
        }
        total_cost += cost;
    }
    return total_cost;
}

int main() {
    vector<map<string, int>> d = parse_data("data.txt");
    int res1 = part1(d);
    cout << res1 << endl;
}