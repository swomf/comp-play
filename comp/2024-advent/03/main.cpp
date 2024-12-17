#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define lli long long int

int main() {
  int a, b, enabled = 1;
  lli total = 0;
  string line;
  while (getline(cin, line)) {
    if (line == "do()") {
      enabled = 1;
      continue;
    } else if (line == "don't()") {
      enabled = 0;
      continue;
    }
    sscanf(line.c_str(), "mul(%d,%d)", &a, &b);
    if (enabled)
      total += (a * b);
  }
  cout << total;
  return 0;
}
