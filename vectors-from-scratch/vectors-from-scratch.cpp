/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

class doublevector {
  static constexpr double DOUBLE_DEFAULT_VALUE = -5.55;
  double *mValues = nullptr;
  int mNumValues = 0;

public:
  doublevector();
  ~doublevector();
  void resize(const int new_size,
              const double initial_value = DOUBLE_DEFAULT_VALUE);
  void push_back(const double value);
  double &at(const int index);
  const double &at(const int index) const;
  unsigned long size() const;
};
void print_all(const doublevector &v) {
  if (v.size() == 0) {
    cout << "Vector is empty.\n";
  } else {
    unsigned long i;
    for (i = 0; i < v.size(); i++) {
      cout << "[" << setfill('0') << right << setw(3) << i << "] = " << fixed
           << setprecision(4) << v.at(i) << '\n';
    }
  }
}
int main() {
  doublevector v;
  do {
    string command;
    cout << "Enter a command ('quit' to quit): ";
    if (!(cin >> command) || command == "quit") {
      break;
    } else if (command == "push_back") {
      double value;
      cin >> value;
      v.push_back(value);
      cout << "Pushed back " << fixed << setprecision(4) << value << '\n';
    } else if (command == "resize") {
      string line;
      int new_size;
      double initial;
      cin >> new_size;
      getline(cin, line);
      istringstream sin(line);

      if (sin >> initial)
        v.resize(new_size, initial);
      else
        v.resize(new_size);
    } else if (command == "size") {
      cout << v.size() << '\n';
    } else if (command == "print") {
      print_all(v);
    } else if (command == "get") {
      int index;
      cin >> index;
      try {
        cout << "Value at " << index << " = " << setprecision(4) << fixed
             << v.at(index) << '\n';
        ;
      } catch (out_of_range &err) {
        cout << err.what() << '\n';
      }
    } else if (command == "set") {
      double d;
      int index;
      cin >> index >> d;
      try {
        v.at(index) = d;
        cout << "SET: " << index << " = " << setprecision(4) << fixed
             << v.at(index) << '\n';
        ;
      } catch (out_of_range &err) {
        cout << err.what() << '\n';
      }
    } else if (command == "clear") {
      v.resize(0);
    } else {
      cout << "Invalid command '" << command << "'\n";
    }
  } while (true);
  cout << endl;
  return 0;
}
// Write your class members below here.

doublevector::doublevector() {}
doublevector::~doublevector() {}

void doublevector::resize(const int new_size, const double initial_value) {}

void doublevector::push_back(const double value) {}

double &doublevector::at(const int index) {}

const double &doublevector::at(const int index) const {}

unsigned long doublevector::size() const {}
