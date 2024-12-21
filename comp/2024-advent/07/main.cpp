#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace std;
#define lli long long int

class Operation {
public:
  // 1 is add, 2 is multiply, 3 is concat
  vector<int> operations;
  Operation(int amount_of_numbers) {
    for (amount_of_numbers--; amount_of_numbers--; operations.push_back(1))
      ;
  }
  // run ops
  lli operate(vector<lli> *vec) {
    /*for (auto i : *vec)
      cout << i << ' ';
    cout << endl;
    for (auto i : operations)
      cout << ' ' << i;
    cout << endl;
*/
    lli sum = (*vec)[0];
    for (int i = 0; i < operations.size(); i++) {
      switch (operations[i]) {
      case 1: // add
        sum += (*vec)[i + 1];
        break;
      case 2: // multiply
        sum *= (*vec)[i + 1];
        break;
      case 3: // concat
        size_t second_size = to_string((*vec)[i + 1]).length();
        sum = sum * pow(10, second_size) + (*vec)[i + 1];
        break;
      }
    }
    return sum;
  }
  // increment self, as if we're counting upwards in ternary
  // returns false if cannot increment anymore
  bool increment() {
    bool is_last = false;
    for (int op : operations) {
      if (op != 3) {
        is_last = true;
      }
    }
    if (!is_last)
      return false;

    for (int i = operations.size() - 1; ++operations[i];) {
      if (operations[i] == 4) {
        operations[i] = 1;
        i--;
      } else
        break;
    }

    return true;
  }
};

int main() {
  lli total = 0;

  for (string line; getline(cin, line);) {
    istringstream iss(line);
    lli test;
    vector<lli> atoms;
    iss >> test;

    for (char skip = '0'; skip != ' '; iss.get(skip)) {
    };
    for (lli atom; iss >> atom; atoms.push_back(atom)) {
    };

    Operation op = Operation(atoms.size());
    do {
      lli s = op.operate(&atoms);
      if (s == test) {
        // printf("WOOOOOOOOOOOOOW: %lld\n", s);
        total += s;
        break;
      }
    } while (op.increment());
  }
  cout << total << endl;
  return 0;
}
