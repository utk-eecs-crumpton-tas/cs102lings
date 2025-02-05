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
//  - auto-format in vim with gg=G in normal mode, in vscode with alt+shift+f
//! Remember: check your solution with the gradescripts
//  - gradescript command: python3.11 scripts/test.py tax.cpp

#include <iomanip> // if using iomanip instead of printf
#include <iostream>

using namespace std;

// You can declare global constants for your salary brackets here
//! Remember, globals that are not const are a formatting error
// (globals, aka variables defined outside of main)
const double MINIMUM_WAGE = 15080;
// bracket1 is 0
const double BRACKET2 = 11600;
const double RATE1 = 0.10;
// TODO: add the rest!

int main() {
    double salary;
    cout << "Enter a salary: $";
    cin >> salary;

    // Handling an error
    if (/* TODO: */) {
        // print an error message to cerr (not cout!)
        // cerr is like cout but for errors
        cerr << "TODO!" << endl;
        return /* TODO */; // exit with an error, non-zero exit code means error
    }

    // TODO: Calculate the take home pay for the given salary
    // - if you find you are repeating yourself, try another way!
    // - You can solve this using the constants defined above only 2 or 3 times.
    // - Do not define code to print your report more than once!!

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

// There are 6 brackets, each correct calculations at each bracket is worth 5
// points (tests 2-14)
// Calculations that are slightly off are only half credit!
// (2.5 points)
