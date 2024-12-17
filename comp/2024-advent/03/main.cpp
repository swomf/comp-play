#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define lli long long int

int main() {
  int a, b;
  lli total = 0;
  string line;
  while (getline(cin, line)) {
    sscanf(line.c_str(), "mul(%d,%d)", &a, &b);
    total += (a * b);
  }
  cout << total;
  return 0;
}
