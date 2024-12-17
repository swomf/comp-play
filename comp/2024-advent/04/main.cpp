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

char letter(vector<string> *grid, int i, int j) { return (*grid)[i][j]; }

int main() {
  vector<string> grid;
  string line;
  long long int total = 0;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].length(); j++) {
      if (i == 0 || j == 0 || i == grid.size() - 1 || j == grid[0].length() - 1)
        continue; // edges
      if (letter(&grid, i, j) != 'A')
        continue;
      char nw = letter(&grid, i - 1, j - 1), ne = letter(&grid, i - 1, j + 1),
           sw = letter(&grid, i + 1, j - 1), se = letter(&grid, i + 1, j + 1);
      int neg_slope = (nw == 'M' && se == 'S') || (nw == 'S' && se == 'M');
      int pos_slope = (sw == 'M' && ne == 'S') || (sw == 'S' && ne == 'M');
      total += (neg_slope && pos_slope);
    }
  }
  cout << total << endl;
  return 0;
}
