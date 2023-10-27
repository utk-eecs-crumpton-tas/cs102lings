/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class BITSET {
    vector<int> mSets;

  public:
    BITSET();
    bool Test(int index) const;
    void Set(int index);
    void Clear(int index);
    int GetNumSets() const;
    int GetSet(int index) const;
};
string ToBinary(int bit_set, int spacing = 4);
int main() {
    BITSET sets;
    string command;
    int which;
    do {
        cout << "> ";
        if (!(cin >> command) || "q" == command) {
            // If cin fails for any reason, it usually means
            // an EOF state, break and quit.
            break;
        }
        // Handle the commands here
        if ("t" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                cout << sets.Test(which) << '\n';
            }
        } else if ("s" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Set(which);
            }
        } else if ("g" == command) {
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin{line};
            if (!(sin >> which)) {
                cout << "Invalid index\n";
            } else {
                if (!(sin >> spacing)) {
                    spacing = 4;
                }
                cout << ToBinary(sets.GetSet(which), spacing) << '\n';
            }
        } else if ("c" == command) {
            // TODO: Finish the "clear" command here.
        }
        // TODO: Finish the rest of the commands here.
        else {
            cout << "Unknown command '" << command << "'\n";
        }
    } while (true);
    return 0;
}
// Write the function body for ToBinary:
string ToBinary(int bit_set, int spacing) {
    string ret;
    // TODO: Add values to the ret string. The constructor will
    // clear it to the empty string "".
    for (int i = 31; i >= 0; i--) {
        // TODO: Write the logical operation that tests the bit at index i
        if (/* ... */) {
            ret += '1';
        } else {
            ret += '0';
        }
        // TODO: Check to see if we need a space here.
        if (/* ... */) {
            ret += ' ';
        }
    }
    return ret;
}

// BITSET Class Members
BITSET::BITSET() : mSets(1, 0) {}

bool BITSET::Test(int index) const {
    // Recall that each set has 32 bits
    int which_set = /* ... */; // TODO: FINISH THE ARITHMETIC HERE
    int which_bit = /* ... */; // TODO: FINISH THE ARITHMETIC HERE
    if (which_set >= GetNumSets()) {
        // The BITSET is an "infinite" set, so if the requested set
        // is bigger than what we are storing, that means it's a 0.
        return false;
    }
    // TODO: Write the code to test the bit at which_set/which_bit
    // and return true if it's a 1 or false if it's a 0.
    return /* ... */;
}

void BITSET::Set(int index) {
    int which_set = /* ... */; // TODO: FINISH THE ARITHMETIC HERE
    int which_bit = /* ... */; // TODO: FINISH THE ARITHMETIC HERE
    // TODO: You might need to expand the Set to accommodate the index
    // which_set. If you do not do this properly, you will get a runtime
    // error named 'out_of_range'
    // TODO: Finish the bitwise operator to set bit which_bit.
    mSets.at(which_set) = /* ... */;
}

void BITSET::Clear(int index) {
    int which_set = /* ... */; // TODO: FINISH THE ARITHMETIC HERE
    int which_bit = /* ... */; // TODO: FINISH THE ARITHMETIC HERE
    if (which_set < GetNumSets()) {
        mSets.at(which_set) = /* ... */; // TODO: Finish the bitwise
                                           // operation(s) to clear bit which_bit.
        // TODO: Write the code here to truncate empty sets--sets that are 0.
    }
}

int BITSET::GetNumSets() const { return static_cast<int>(mSets.size()); }

int BITSET::GetSet(int which_set) const {
    // TODO: Check to see if index exists!
    return mSets.at(which_set);
}