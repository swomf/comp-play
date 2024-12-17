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
  lli sim = 0;
  for (int i : l1) {
    for (int j : l2) {
      if (i == j)
        sim += i;
    }
  }
  cout << sim << endl;
  return 0;
}
