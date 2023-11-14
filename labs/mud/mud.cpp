/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

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
    // TODO
}

// Use for debugging
void dumpRooms(const Room *const rooms, const size_t roomCount) {
    for (size_t i = 0; i < roomCount; ++i) {
        cerr << "Room " << i << endl;
        cerr << "  name: " << rooms[i].name << endl;
        cerr << "  description: " << rooms[i].description << endl;
        cerr << "  north: " << rooms[i].north << endl;
        cerr << "  south: " << rooms[i].south << endl;
        cerr << "  east: " << rooms[i].east << endl;
        cerr << "  west: " << rooms[i].west << endl;
    }
}

// Removes whitespace inplace from the front and back of a string.
// "\n hello\n \n" -> "hello"
void stripWhitespace(string &str) {
    while (isspace(str.back())) {
        str.pop_back();
    }
    while (isspace(str.front())) {
        str.erase(str.begin());
    }
}

// Take in a char 'n', 's', 'e', or 'w' and return the full direction name.
// e.g. 'n' -> "NORTH"
// Helpful for converting user input to direction names.
string getDirectionName(const char direction) {}

const Room *loadRooms(const char *const dungeonFilename) {
    // - Open the file.
    // - Count the number of tildes in the file.
    //   There are 3 tildes per room.
    // - Allocate the correct number of rooms using the new operator.
    // - Jump back to the beginning of the file. You can do so with
    //     fin.clear(); // Clear the error
    //     fin.seekg(0); // Jump back to the beginning
    // - Read through the file again, this time reading in the rooms.
    // - Remember to free your rooms with `delete[]` outside of this function!!
    // - Remember to close your file!

    size_t tildeCount; // TODO
    size_t roomCount;  // TODO

    Room *rooms = new Room[roomCount];

    // Read in the rooms
    for (size_t i = 0; i < roomCount; i++) {
        // - You can use getline with '~' to read in the 3 fields.
        // - Use `stripWhitespace` to remove any extra whitespace from the
        //   fields.
        // - The 3rd field, exits, will require more processing,
        //   you can use an `istringstream` for this. All fields are delimited
        //   by whitespace so you can use the extraction operation (>>).
    }

    // dumpRooms(rooms, roomCount); // uncomment for debugging

    // TODO: return your rooms
}

int main(int argc, char **argv) {
    // - Read the filename from argv
    // - Load your Rooms
    // - Remember to free your rooms with `delete[]`!

    int currentRoom = 0; // Start at room 0

    while (true) {

        char input;
        cout << "> ";
        cin >> input;

        switch (input) {
            // quit (q)

            // look (l)

            // navigate (n, s, e, w)

            // invalid input: do nothing
        }
    }

    return 0;
}