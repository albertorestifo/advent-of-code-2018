#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Recursive function to calculate the difference between strings
void diff_strings(string a, string b, int* diff)
{
    char a_head = a.front();
    char b_head = b.front();

    if (a_head != b_head) {
        *diff += 1;
    }

    int a_len = a.length();
    int b_len = a.length();

    // Exit condition: the string is only 1 long, which means there is no
    // tail
    if (a_len == 1)
        return;

    string a_tail = a.substr(1, a_len);
    string b_tail = b.substr(1, b_len);

    return diff_strings(a_tail, b_tail, diff);
}

int main()
{
    ifstream infile("puzzle.in");
    string line;

    // Load all the ids in memory
    vector<string> ids;
    while (getline(infile, line)) {
        ids.push_back(line);
    }

    // Find a matching pair
    for (auto a : ids) {
        for (auto b : ids) {
            // Ingore the same id
            if (a == b)
                continue;

            int diff = 0;
            diff_strings(a, b, &diff);
            if (diff == 1) {
                string common = "";
                for (unsigned i = 0; i < a.length(); ++i) {
                    if (a[i] == b[i]) {
                        common.push_back(a[i]);
                    }
                }

                cout << "A: " << a << endl;
                cout << "B: " << b << endl;
                cout << "Common letters: " << common << endl;
                return 0;
            }
        }
    }
}
