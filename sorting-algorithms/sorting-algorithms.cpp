/* TODO: Don't forget your header and to comment your code! */
#include <iostream>
#include <vector>
using namespace std;

void printVector(vector <int> &vec) {
  for (int i = 0; i < vec.size(); ++i) {
    cout << "  " << vec.at(i);
  }
  cout << "\n";
}

int main() {
  vector <int> data;

  return 0;
}