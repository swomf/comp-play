#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

void recursive_walk(vector<string> *grid, int i, int j, char dir, int *walked) {
  cout << "====================" << endl;
  for (string s : *grid) {
    cout << s << endl;
  }
  char *cur = &((*grid)[i][j]);
  if (*cur != 'X') {
    *cur = 'X';
    (*walked)++;
  }
change_direction:
  int next_i = i + (dir == 'N' ? -1 : dir == 'S' ? 1 : 0);
  int next_j = j + (dir == 'W' ? -1 : dir == 'E' ? 1 : 0);
  if (next_i >= 0 && next_i < grid->size() && next_j >= 0 &&
      next_j < (*grid)[0].length()) {
    char next_block = (*grid)[next_i][next_j];
    if (next_block == '#') {
      dir = dir == 'N' ? 'E' : dir == 'E' ? 'S' : dir == 'S' ? 'W' : 'N';
      goto change_direction;
    }
    recursive_walk(grid, next_i, next_j, dir, walked);
  }
}

int main() {
  vector<string> grid;
  int i = 0, s_i, s_j, walked = 0;
  for (string line; cin >> line;) {
    grid.push_back(line);
    for (int j = 0; j < line.length(); j++) {
      if (line[j] == '^') {
        s_i = i; // save center
        s_j = j;
      }
    }
    i++;
  }
  recursive_walk(&grid, s_i, s_j, 'N', &walked);

  cout << walked << endl;

  return 0;
}
