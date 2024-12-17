#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define lli long long int

void cmp(int prev, int next, int decreasing, int *safety) {
  int diff = abs(prev - next);
  cout << prev << ' ' << next
       << ((prev > next) ? " decreases by " : " increases by ") << diff << '\n';
  if (diff < 1 || diff > 3 || (prev > next != decreasing)) {
    *safety = 0;
    cout << "                       REJECTED\n";
  }
}

int main() {
  string line;
  lli total = 0;
  while (getline(cin, line)) {
    cout << "==============" << endl;
    istringstream iss(line);
    int prev, next, safety = 1, decreasing;
    iss >> prev >> next;
    decreasing = (prev > next);
    cmp(prev, next, decreasing, &safety);
    prev = next;
    while (iss >> next && safety) {
      cmp(prev, next, decreasing, &safety);
      prev = next;
    }
    total += safety;
  }
  cout << total;
  return 0;
}
