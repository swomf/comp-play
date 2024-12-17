#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define lli long long int

int main() {
  vector<int> l1, l2;
  string line;
  int a, b;
  while (cin >> a >> b && !cin.eof()) {
    l1.push_back(a);
    l2.push_back(b);
  }
  sort(l1.begin(), l1.end());
  sort(l2.begin(), l2.end());
  lli dist = 0;
  for (int i = 0; i < l1.size(); i++) {
    int add = abs(l1[i] - l2[i]);
    cout << l1[i] << " - " << l2[i] << " = " << add << endl;
    dist += add;
  }
  cout << dist << endl;
  return 0;
}
