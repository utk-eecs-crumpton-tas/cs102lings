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
//  - gradescript command: python3.11 scripts/test.py mud.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Room {
    int north = -1; // -1 means no room
    int south = -1;
    int east = -1;
    int west = -1;
    string name;
    string description;
};

// Take in a direction char, return the room index in that direction.
int getExit(const Room &room, const char direction) {
    // TODO
}

// Take in a direction char and index and assign the exit to the room.
void setExit(Room &room, const char direction, const int roomIndex) {
    // TODO
}

// Take in a name and description and assign them to the room.
void setInfo(Room &room, const string &name, const string &description) {
    // TODO
}

// Print the room's name, description, and exits.
void look(const Room &room) {
    // - name and description will be on their own line.
    // - There will be a blank line between the description and exits.
    // - Exits will be on their own line with a space between each exit.
    //   e.g. "Exits: n s e w"
    // - Make sure your exits do not have a trailing space.
    //   e.g. "Exits: n s e w " <-
}

// For debugging
void dumpRooms(const Room *const rooms, const size_t roomCount) {
    cout << "Room count: " << roomCount << endl;
    for (size_t i = 0; i < roomCount; ++i) {
        cout << "Room " << i << endl;
        cout << "  name: " << rooms[i].name << endl;
        cout << "  description: " << rooms[i].description << endl;
        cout << "  north: " << rooms[i].north << endl;
        cout << "  south: " << rooms[i].south << endl;
        cout << "  east:  " << rooms[i].east << endl;
        cout << "  west:  " << rooms[i].west << endl;
    }
}

// Removes whitespace inplace from the front and back of a string.
// "\n hello\n \n" -> "hello"
void stripWhitespace(string &str) {
    while (!str.empty() && isspace(str.back())) {
        str.pop_back();
    }
    while (!str.empty() && isspace(str.front())) {
        str.erase(str.begin());
    }
}

// Take in a char 'n', 's', 'e', or 'w' and return the full direction name.
// e.g. 'n' -> "NORTH"
// Helpful for converting user input to direction names.
string getDirectionName(const char direction) {}

const Room *loadRooms(const string dungeonFilename) {
    // - Open the file.
    // - Count the number of tildes in the file.
    //   There are 3 tildes per room.
    // - If the file does not open, you can exit `exit(1);` to exit inside of a
    //   function.
    // - Allocate the correct number of rooms using the new operator.
    // - Jump back to the beginning of the file. You can do so with
    //     fin.clear(); // Clear the error
    //     fin.seekg(0); // Jump back to the beginning
    // - Read through the file again, this time reading in the rooms.
    // - Remember to free your rooms with `delete[]` outside of this function!!
    // - Remember to close your file!

    size_t tildeCount = 0; // TODO
    size_t roomCount = 0;  // TODO

    Room *rooms = new Room[roomCount];

    // Read in the rooms
    for (size_t i = 0; i < roomCount; i++) {
        // - You can use getline with '~' to read in the 3 fields.
        // - Use `stripWhitespace` to remove any extra whitespace from the
        //   fields.
        // - The 3rd field, exits, will require more processing,
        //   you can use an `istringstream` and a while loop for this.
        //   All fields are delimited by whitespace so you can use the
        //   extraction operation (>>).
    }

    // Make sure your rooms are correct before continuing!
    dumpRooms(rooms, roomCount);

    // TODO: return your rooms.
}

int main(int argc, char **argv) {
    // - Read the filename from argv
    // - Load your Rooms
    // - Remember to free your rooms with `delete[]`!!

    int currentRoom = 0; // Start at room 0

    while (true) {

        char input;
        cout << "> ";
        cin >> input;

        switch (input) {
            // quit (q)

            // look (l)

            // navigate (n, s, e, w)
            // - You can use getExit and getDirectionName to combine all 4 cases
            //   into 1

            // invalid input: do nothing
        }
    }

    return 0;
}