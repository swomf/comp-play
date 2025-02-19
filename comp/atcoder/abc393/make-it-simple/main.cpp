#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  unsigned rm = 0;
  set<set<int>> s;
  for (int a, b; m--;) {
    cin >> a >> b;
    if (a == b) {
      rm++;
      // printf("%d = %d\n", a, b);
      continue;
    }
    size_t size = s.size();
    s.insert(set<int>({a, b}));
    if (s.size() == size) {
      // printf("duplicate (%d, %d)\n", a, b);
      rm++;
    }
  }
  cout << rm << endl;
  return 0;
}
