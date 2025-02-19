#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int len, ict, first, mid, mid_mid, last;
  long long int moves = 0;
  string s;
  vector<int> indices = vector<int>();
  cin >> len >> s;
  for (int i = 0; i < len; i++)
    if (s[i] == '1')
      indices.push_back(i);

  /* select middle 1 and move others into adjacency */
  first = indices[0];
  ict = indices.size();
  mid_mid = ict / 2;
  mid = indices[mid_mid];
  last = indices[ict - 1];

  for (int i = 1; mid_mid - i >= 0; i++) {
    int num = indices[mid_mid - i];
    moves += (mid - num - i);
  }
  for (int i = 1; mid_mid + i < ict; i++) {
    int num = indices[mid_mid + i];
    moves += (num - mid - i);
  }
  cout << moves << endl;

  return 0;
}
