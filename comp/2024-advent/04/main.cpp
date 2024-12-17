#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

// recursively check for existence
int existence(vector<string> *grid, int i, int j, int i_walk, int j_walk,
              int step, int print) {
  if (i < 0 || j < 0 || i >= (*grid).size() || j >= (*grid)[0].length())
    return 0; // oob
  char cmp = step == 1   ? 'X'
             : step == 2 ? 'M'
             : step == 3 ? 'A'
             : step == 4 ? 'S'
                         : '\n'; // placeholder
  char cur = (*grid)[i][j];
  if (print)
    cout << "(" << i << ',' << j << ") =" << cur << cmp << step;
  if (cur != cmp)
    return 0; // failed comparison
  if (step == 4)
    return 1; // ended
  return existence(grid, i + i_walk, j + j_walk, i_walk, j_walk, step + 1,
                   print);
}

int main() {
  vector<string> grid;
  string line;
  long long int total = 0;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].length(); j++) {
      for (int i_walk = -1; i_walk <= 1; i_walk++) {
        for (int j_walk = -1; j_walk <= 1; j_walk++) {
          if (i_walk == 0 && j_walk == 0)
            continue;
          int found = existence(&grid, i, j, i_walk, j_walk, 1, 0);
          if (found) {
            cout << "Found at " << i << ' ' << j << " with step " << i_walk
                 << " " << j_walk;
            existence(&grid, i, j, i_walk, j_walk, 1, 1);
            cout << endl;
          }
          total += found;
        }
      }
    }
  }
  cout << total << endl;
  return 0;
}
