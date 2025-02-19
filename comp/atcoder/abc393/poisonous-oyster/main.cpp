#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  string t12, a13;
  unsigned int world = 0b1111; // each oyster
  cin >> t12 >> a13;
  if (t12[0] == 's') {
    world &= 0b1100;
  } else {
    world &= 0b0011;
  }
  if (a13[0] == 's') {
    world &= 0b1010;
  } else {
    world &= 0b0101;
  }
  for (int i = 1; i <= 4; i++) {
    if (world >> (4 - i) & 1) {
      cout << i << endl;
    }
  }
  return 0;
}
