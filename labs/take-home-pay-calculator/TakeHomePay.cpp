/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

// Remember your header! 5 points
// Remember your comments! 5 points
// Remember your formatting!

#include <iomanip> // if using iomanip
#include <iostream>

using namespace std;

// You can declare global constants for your salary brackets here
//! Remember, globals that are not const are a formatting error
const double MINIMUM_WAGE = 15080;
const double BRACKET1 = 10275;
const double BRACKET1_RATE = 0.10;
// etc.

int main() {

  double salary;
  cout << "Enter a salary: $";
  cin >> salary;

  // Handling an error
  if (salary <= MINIMUM_WAGE) {
    // print an error message to cerr (not cout!)
    // cerr is like cout but for errors
    cerr << "This is less than minimum wage for a yearly salary." << endl;
    return 1; // exit with an error, non-zero exit code means error
  }

  // TODO: Calculate the take home pay for the given salary

  // Examples of output formatting (delete these)
  // how to left justify by 9 and print 2 sig figs with printf
  printf("%-9.2f\n", salary);
  // how to right justify by 9 and print 2 sig figs with printf
  printf("%9.2f\n", salary);

  // set iomanip to print 2 with sig figs  (only needed once!)
  cout << fixed << setprecision(2);

  // how to left justify by 9 with iomanip
  cout << left << setw(9) << salary << endl;
  // how to right justify by 9 with iomanip
  cout << right << setw(9) << salary << endl;

  return 0;
}

// Remember to check your calculations and output with the gradescripts!
// There are 6 brackets, each calculation is worth 5 points (tests 2-7)
// Calculations that are slightly off are only half credit! (2.5 points)