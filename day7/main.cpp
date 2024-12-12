
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
	while(getline(inputFile, line)) {
		v_out.push_back(line);
	}
	return v_out;
}

bool checker(unsigned long long target, vector<unsigned long long>& v, int idx, unsigned long long a) {
	if (idx==v.size()-1) {
		if (target==a+v[idx] || target==a*v[idx]) {
			return true;
		} else {
			return false;
		}
	}
	bool plus = false;
	bool mult = false;
	if (idx==0) {
		plus = checker(target, v, idx+1, v[idx]); // +
		mult = checker(target, v, idx+1, v[idx]); // *
	} else {
		plus = checker(target, v, idx+1, a+v[idx]); // +
		mult = checker(target, v, idx+1, a*v[idx]); // *
	}
	return (plus || mult);
}

int part1(vector<string> v_in) {
	unsigned long long retval = 0;
	for (const string& s : v_in) {
		string str_target = s.substr(0, s.find(':'));
		string str_xs = s.substr(s.find(':')+2, s.length());
		unsigned long long target = stoull(str_target);
		stringstream ss(str_xs);
		unsigned long long token;
		vector<unsigned long long> xs;
		while (ss >> token){
			xs.push_back(token);
		}
		bool ok = checker(target, xs, 0, 0);
		// cout << ok << endl;
		if (ok) {
			retval += target;
			cout << target << endl;
		}
		// cout << retval << endl;
	}
	return retval;
}

unsigned long long num_concatter(unsigned long long a, unsigned long long b) {
	string a_str = to_string(a);
	string b_str = to_string(b);
	string c_str = a_str+b_str;
	return stoull(c_str);
}

bool checker_concat(unsigned long long target, vector<unsigned long long>& v, int idx, unsigned long long a) {
	if (idx==v.size()-1) {
		if (target==a+v[idx] || target==a*v[idx] || target==num_concatter(a, v[idx])) {
			return true;
		} else {
			return false;
		}
	}
	bool plus = false;
	bool mult = false;
	bool concat = false;
	if (idx==0) {
		plus = checker_concat(target, v, idx+1, v[idx]); // +
		mult = checker_concat(target, v, idx+1, v[idx]); // *
		concat = checker_concat(target, v, idx+1, v[idx]); // concat
	} else {
		plus = checker_concat(target, v, idx+1, a+v[idx]); // +
		mult = checker_concat(target, v, idx+1, a*v[idx]); // *
		concat = checker_concat(target, v, idx+1, num_concatter(a, v[idx])); // concat
	}
	return (plus || mult || concat);
}

int part2(vector<string> v_in) {
	unsigned long long retval = 0;
	for (const string& s : v_in) {
		string str_target = s.substr(0, s.find(':'));
		string str_xs = s.substr(s.find(':')+2, s.length());
		unsigned long long target = stoull(str_target);
		stringstream ss(str_xs);
		unsigned long long token;
		vector<unsigned long long> xs;
		while (ss >> token){
			xs.push_back(token);
		}
		bool ok = checker_concat(target, xs, 0, 0);
		// cout << ok << endl;
		if (ok) {
			retval += target;
			cout << target << endl;
		}
		// cout << retval << endl;
	}
	return retval;
}

int main() {
	vector<string> d = parse_data("data.txt");
	// unsigned long long res1 = part1(d);
	// cout << res1 << endl;
	unsigned long long res2 = part2(d);
	cout << res2 << endl;
}


