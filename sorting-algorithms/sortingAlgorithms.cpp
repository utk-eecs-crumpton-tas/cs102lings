/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> &vec) {
  for (int i = 0; i < vec.size(); ++i) {
    cout << "  " << vec.at(i);
  }
  cout << "\n";
}

int main() {
  vector<int> data;

  return 0;
}