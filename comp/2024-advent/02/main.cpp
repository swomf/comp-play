#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define lli long long int

/**
 * returns first index of failure. -1 if safe.
 */
int inspect(vector<int> *v) {
  int decreasing = (*v)[0] > (*v)[1];
  for (int i = 0; i < v->size() - 1; i++) {
    int prev = (*v)[i], next = (*v)[i + 1];
    int diff = abs(prev - next);
    cout << prev << ' ' << next
         << ((prev > next) ? " decreases by " : " increases by ") << diff
         << '\n';
    if (prev > next != decreasing || diff < 1 || diff > 3) {
      cout << " REJECTED !!! \n";
      return i;
    }
  }
  return -1;
}

int retry() {
  cout << "        retry ===========\n";
  return 0;
}

int main() {
  string line;
  lli total = 0;
  while (getline(cin, line)) {
    cout << "==========================" << endl;
    istringstream iss(line);
    vector<int> v;
    int k;
    while (iss >> k)
      v.push_back(k);
    int failure_index = inspect(&v);
    if (failure_index == -1) {
      // Case 1: Safe on first try
      total++;
      continue;
    } else {
      int done = 0;
      for (int i = 0; i < v.size() && !done; i++) {
        vector<int> v_new = v;
        v_new.erase(v_new.begin() + i);
        if (inspect(&v_new) == -1) {
          total++;
          done = 1;
        }
      }
    }
  }
  cout << total;
  return 0;
}
