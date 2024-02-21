/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

//! Remember: your comments
//! Remember: your formatting and indentation
//  - auto-format in vim: gg=G in normal mode, in vscode: alt+shift+f
//! Remember: check your solution with the gradescripts
//  - gradescript command: `python3.11 scripts/test.py speeding.cpp`
//! Remember: to error check and close your files

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

//! Remember: non-const globals are a penalty
//    "non-const globals" aka variables defined outside of a function e.g. main
//    without the const keyword are a penalty on your grade

const string THREE_LETTER_MONTHS[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
};

const double INTERSTATE_MULTIPLIER = 0 /* TODO */;
const double HIGHWAY_MULTIPLIER = 0 /* TODO */;
const double RESIDENTIAL_MULTIPLIER = 0 /* TODO */;
const double DEFAULT_MULTIPLIER = 0 /* TODO */;

int serializeDate(const int year, const int month, const int day) {
    // TODO: combine the month, day, and year into a single integer
    //   in the form YYYYMMDD to easily compare dates
    // Make sure the year is 4 digits YYYY before calling this function
    // Do not use any strings or string functions, just arithmetic
    // Example usage:
    //   int serialStartDate = serializeDate(startYear, startMonth, startDay);
    // Example output:
    //   20081125 = serializeDate(2008, 11, 25);
    int serialDate;

    return serialDate;
}

int main() {
    // - HINT: You do not need vectors for this lab, you can write each line of
    //   output directly to the output file
    // - HINT: You do not need `getline` or `stringstreams`
    //   you can use the format while(fin >> citationNumber >> month >> ...)
    //   to read out the fields of data from each line
    // - HINT: remember to check if your file opened,
    //   and close it once finished

    // TODO

    return 0;
}