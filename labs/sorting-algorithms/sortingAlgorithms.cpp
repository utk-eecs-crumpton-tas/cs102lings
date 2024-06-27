/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE
 * Sources: Cite any instructors, students, or external resources you used here.
 *   - Do not directly copy code from any source:
 *     other students, Stack Overflow, ChatGPT, etc.
 *   - Do not include code in your solution you do not understand or cannot
 *     explain.
 *   - We check plagiarism for similarities and irregularities.
 */

//! Remember: your comments
//! Remember: your formatting and indentation
//  - auto-format in vim: gg=G in normal mode, in vscode: alt+shift+f
//! Remember: check your solution with the gradescripts
//  - gradescript command: python3.11 scripts/test.py sortingAlgorithms.cpp

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << "  " << vec.at(i);
    }
    cout << "\n";
}

void swapValues(std::vector<int> &values, const size_t left_index,
                const size_t right_index) {
    // TODO
}

void selectionSort(std::vector<int> &values) {
    // TODO
}

int main() {
    vector<int> data;

    return 0;
}