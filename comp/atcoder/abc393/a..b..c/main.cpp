#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  string n;
  cin >> n;
  unsigned int tot = 0;
  for (int i = 0; i < n.length(); i++) {
    if (n[i] != 'B')
      continue;
    for (int j = 0; i - j >= 0 && i + j < n.length(); j++) {
      if (n[i - j] != 'A' || n[i + j] != 'C')
        continue;
      // printf("%d %d %d\n", i - j + 1, i + 1, i + j + 1);
      tot++;
    }
  }
  cout << tot << endl;
  return 0;
}
