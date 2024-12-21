#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

class Coord {
public:
  int i, j;
  char t;
  Coord(int i, int j, char t) : i(i), j(j), t(t) {};
  bool double_distance_to(int cur_i, int cur_j, Coord *otherCoord) {
    if (t != otherCoord->t)
      return false; // Must be same "frequency"

    int this_di = i - cur_i, this_dj = j - cur_j,
        other_di = otherCoord->i - cur_i, other_dj = otherCoord->j - cur_j;

    bool yea = (this_di == other_di * 2 && this_dj == other_dj * 2) ||
               (this_di * 2 == other_di && this_dj * 2 == other_dj);
    if (yea) {
      printf("YEAHHHHHHHHHHHHHHHHHHHHHHHH!\n");
    }
    printf("(%d %d) distances:\n\t(%d %d %c)=%d %d\n\t(%d %d %c)=%d %d\n",
           cur_i, cur_j, i, j, t, this_di, this_dj, otherCoord->i,
           otherCoord->j, otherCoord->t, other_di, other_dj);

    return yea;
  }
};

int main() {
  vector<string> grid;
  vector<Coord> antennas;
  int i = 0;
  for (string line; cin >> line; i++) {
    grid.push_back(line);
    for (int j = 0; j < line.length(); j++) {
      char c = line[j];
      if (c != '.') {
        antennas.push_back(Coord(i, j, c));
      }
    }
  }
  cout << "initialized to " << antennas.size() << endl;

  set<tuple<int, int>> antis;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].length(); j++) {
      for (int compare0 = 0; compare0 < antennas.size() - 1; compare0++) {
        for (int compare1 = compare0 + 1; compare1 < antennas.size();
             compare1++) {
          if (antennas[compare0].double_distance_to(i, j,
                                                    &antennas[compare1])) {
            antis.insert(make_tuple(i, j));
            grid[i][j] = '#';
            goto nextly;
          }
        }
      }
    nextly:
      int p;
    }
  }
  for (string s : grid)
    cout << s << endl;
  cout << antis.size();

  return 0;
}
