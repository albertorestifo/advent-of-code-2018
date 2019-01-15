#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  int frequency = 0;
  set<int> seen;
  set<int>::iterator it;

  while (1) {
    ifstream infile("puzzle.in");
    string line;
    while (getline(infile, line)) {
      int value = stoi(line);
      frequency += value;

      it = seen.find(frequency);
      if (it != seen.end()) {
        cout << "Found duplicated frequency: " << frequency << endl;
        return 0;
      }

      seen.insert(frequency);
    }
  }
  return 0;
}
