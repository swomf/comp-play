#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_set>
#include <vector>
using namespace std;

using Visited = unordered_set<uint32_t>;
enum Cardinal { NORTH, EAST, SOUTH, WEST };
enum MoveResponse { OOB, BLOCKED, DUPLICATE, NORMAL };

// so you can hypothesize block paths in multiple threads.
class Blocklist {
public:
  void insert(int value) {
    std::lock_guard<std::mutex> lock(mutex_);
    set_.insert(value);
  }

  bool find(int value) {
    std::lock_guard<std::mutex> lock(mutex_);
    return set_.find(value) != set_.end();
  }

  size_t size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return set_.size();
  }

private:
  std::unordered_set<uint32_t> set_;
  std::mutex mutex_;
};

class Movement {
public:
  uint8_t i;
  uint8_t j;
  Cardinal dir;
  Movement(uint8_t i, uint8_t j, Cardinal dir) : i(i), j(j), dir(dir) {}
  Movement(uint32_t encoding) {
    i = 0xFF & (encoding);
    j = 0xFF & (encoding >> 8);
    dir = static_cast<Cardinal>(0xFF & (encoding >> 16));
  }
  uint32_t encode() { return (i) | (j << 8) | (dir << 16); }
  uint32_t encode(uint8_t i_, uint8_t j_, Cardinal dir_) {
    return (i_) | (j_ << 8) | (dir_ << 16);
  }
  // does not memoize if oob, blocked, or duplicate
  // handles turning for you
  MoveResponse move(shared_ptr<Visited> v, shared_ptr<vector<string>> grid,
                    shared_ptr<Blocklist> blocklist,
                    shared_ptr<vector<thread>> workers,
                    bool want_to_test_blocking) {
    uint8_t next_i = i, next_j = j;
    (*grid)[i][j] = 'X';
    // cout << "=========================\n";
    //  printf("%d %d %s, %.24b\n", i, j,
    //        want_to_test_blocking ? "readying" : "blocking", encode());

    // for (string s : *grid) {
    //   cout << s << endl;
    // }
    //  */

    // Check memo
    if (v->find(encode()) != v->end()) {
      // cout << "Duplicate\n";
      return DUPLICATE;
    }
    v->insert(encode());

    // Directional checking, forecast next space
    switch (dir) {
    case NORTH:
      if (i == 0)
        return OOB;
      next_i--;
      break;
    case EAST:
      if (j == (*grid)[0].length() - 1)
        return OOB;
      next_j++;
      break;
    case SOUTH:
      if (i == (*grid).size() - 1)
        return OOB;
      next_i++;
      break;
    case WEST:
      if (j == 0)
        return OOB;
      next_j--;
      break;
    }
    // printf("Next space is %d %d\n", next_i, next_j);

    // Analyze what's ahead. Turn if blocked
    char block = (*grid)[next_i][next_j];
    if (block == 'O' || block == '#') {
      // cout << "Blocked\n";
      dir = static_cast<Cardinal>((dir + 1) % 4);
      return move(v, grid, blocklist, workers,
                  want_to_test_blocking); // At most, ~4 nested recursions
    }

    // try blocking the thing in front of you.
    // we need to have not already crossed it before.
    if (want_to_test_blocking && (*grid)[next_i][next_j] != 'X') {
      shared_ptr<Visited> test_v = make_shared<Visited>(*v);
      shared_ptr<vector<string>> test_grid = make_shared<vector<string>>(*grid);
      (*test_grid)[next_i][next_j] = 'O';
      // printf("Imagined block at %d %d\n", next_i, next_j);
      shared_ptr<Movement> test_movement = make_shared<Movement>(
          Movement(i, j, static_cast<Cardinal>((dir + 1) % 4)));
      shared_ptr<MoveResponse> res = make_shared<MoveResponse>(NORMAL);

      // workers->push_back(thread([res, test_movement, test_v, test_grid,
      //                            blocklist, workers, next_i, next_j, this]()
      //                            {
      while (true) {
        *res =
            test_movement->move(test_v, test_grid, blocklist, workers, false);
        if (*res == DUPLICATE) {
          blocklist->insert(encode(next_i, next_j,
                                   static_cast<Cardinal>(0))); // Directionless
          break;
        } else if (*res == OOB)
          break;
      }
      //}));
    }

    // else, move forward
    i = next_i;
    j = next_j;
    return NORMAL;
  }
};

int main() {
  shared_ptr<Visited> visited = make_shared<Visited>();
  shared_ptr<Blocklist> blocklist = make_shared<Blocklist>();
  shared_ptr<vector<string>> grid = make_shared<vector<string>>();
  shared_ptr<vector<thread>> workers = make_shared<vector<thread>>();
  int i = 0, s_i, s_j, walked = 0;
  for (string line; cin >> line; i++) {
    grid->push_back(line);
    for (int j = 0; j < line.length(); j++) {
      if (line[j] == '^') {
        s_i = i; // save center
        s_j = j;
      }
    }
  }
  for (Movement m = Movement(s_i, s_j, NORTH);
       m.move(visited, grid, blocklist, workers, true) != OOB;) {
  }
  for_each(workers->begin(), workers->end(), [](std::thread &t) { t.join(); });

  cout << blocklist->size() << endl;

  return 0;
}
