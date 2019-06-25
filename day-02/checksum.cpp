#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream infile("puzzle.in");
    string line;

    unordered_map<char, int> linesum;
    unordered_map<int, int> sum;

    while (getline(infile, line)) {
        linesum.clear();

        for (auto c : line) {
            linesum[c]++;
        }

        unordered_map<int, bool> seen;
        for (auto t : linesum) {
            if (t.second > 1 && !seen[t.second]) {
                seen[t.second] = true;
                sum[t.second]++;
            }
        }
    }

    // Calculate the file checksum
    int res = 1;
    for (auto s : sum) {
        res *= s.second;
    }

    cout << "Checksum: " << res << endl;
}
