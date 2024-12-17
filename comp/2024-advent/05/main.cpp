#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
  vector<tuple<int, int>> rules;
  string line;
  // sec1
  for (int a, b; getline(cin, line);) {
    if (line.empty()) {
      break; // section done
    }
    sscanf(line.c_str(), "%d|%d", &a, &b);
    rules.push_back(make_tuple(a, b));
  }
  long long int middles = 0;
  // sec2
  while (getline(cin, line)) {
    vector<int> v;
    istringstream iss(line);
    for (int i; iss >> i;) {
      v.push_back(i);
      cout << i << ' ';
      if (iss.peek() == ',')
        iss.ignore();
    }
    cout << " is ";
    for (int i = 0; i < v.size() - 1; i++) {
      int iv = v[i];
      for (int j = i + 1; j < v.size(); j++) {
        int jv = v[j];
        for (const auto &tup : rules) {
          int in = get<0>(tup), out = get<1>(tup);
          if (in == jv && out == iv) {
            cout << "bad!\n";
            goto bad;
          }
        }
      }
    }
    cout << "good!\n";
    middles += v[v.size() / 2]; // odd middle
  bad:
    int x;
  }
  cout << middles;
  return 0;
}
