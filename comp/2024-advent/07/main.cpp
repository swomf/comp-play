#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace std;
#define lli long long int

enum OPERATION { NONE, ADD, MULT };

int main() {
  lli sum = 0;

  for (string line; getline(cin, line);) {
    istringstream iss(line);
    lli test;
    vector<lli> atoms;
    iss >> test;

    for (char skip = '0'; skip != ' '; iss.get(skip)) {
    };
    for (lli atom; iss >> atom; atoms.push_back(atom)) {
    };

    // left to right
    // 0 = add
    // 1 = multiply
    // [1, (n zeroes)] where n is the amount of edges between numbers.
    printf("line: %b\t\t wants %lld \n", 1 << (atoms.size() - 1), test);
    for (lli i = 0b0; i < (1 << (atoms.size() - 1)); i++) {
      vector<lli> test_atoms = atoms;
      vector<OPERATION> operations;
      for (lli j = 1; j ^ (1 << (atoms.size() - 1)); j <<= 1) {
        operations.push_back(j & i ? MULT : ADD);
      }
      for (lli a : test_atoms) {
        printf("%lld ", a);
      }
      cout << endl;
      for (lli op : operations) {
        printf(" %lld", op);
      }
      cout << endl;

      for (lli i = 0; i < operations.size(); i++) {
        if (operations[i] == MULT) {
          test_atoms[i] = test_atoms[i] * test_atoms[i + 1];
          test_atoms.erase(test_atoms.begin() + i + 1);
          operations.erase(operations.begin() + i);
          i--;

        } else if (operations[i] == ADD) {
          test_atoms[i] = test_atoms[i] + test_atoms[i + 1];
          test_atoms.erase(test_atoms.begin() + i + 1);
          operations.erase(operations.begin() + i);
          i--;

        } else {
          perror("what?\n");
          return 1;
        }
      }
      cout << "sum : " << test_atoms[0] << endl;
      if (test_atoms[0] == test) {
        printf("YAAAAAAAAAAY %lld\n", test_atoms[0]);
        sum += test_atoms[0];
        break;
      }
    }
    printf("\n");
  }
  printf("%lld\n", sum);
  return 0;
}
