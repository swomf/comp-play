#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// greatest to least via second element (idx 1) of tuple
auto cmp = [](const tuple<int, int> &a, const tuple<int, int> &b) {
  return get<1>(b) < get<1>(a);
};

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
    vector<tuple<int, int>> v;
    istringstream iss(line);
    for (int i; iss >> i;) {
      v.push_back(make_tuple(i, 0));
      cout << i << ' ';
      if (iss.peek() == ',')
        iss.ignore();
    }
    for (int i = 0; i < v.size(); i++) {
      int iv = get<0>(v[i]);
      for (int j = 0; j < v.size(); j++) {
        if (i == j)
          continue;
        int jv = get<0>(v[j]);
        for (const auto &tup : rules) {
          int in = get<0>(tup), out = get<1>(tup);
          if (in == iv && out == jv) {
            get<1>(v[i])++; // count amount of befores
          }
        }
      }
    }
    for (int i = 0; i < v.size() - 1; i++) {
      if (get<1>(v[i]) > get<1>(v[i + 1])) {
        // n-1 befores, decreases further as you go along, iff correct order

      } else {
        // wrong order lol. this is what we need for part 2
        goto pass;
      }
    }
    continue; // to get to this line, you are in the correct order.
    // middles += get<0>(v[v.size() / 2]);
  pass:
    sort(v.begin(), v.end(), cmp);
    middles += get<0>(v[v.size() / 2]);
  }
  cout << middles;
  return 0;
}
