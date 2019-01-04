#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream infile("input");

  int frequency;

  string line;
  while (getline(infile, line)) {
    int value = stoi(line);
    frequency += value;
  }

  cout << "Result frequency: " << frequency << endl;

  return 0;
}
