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
//  - gradescript command: python3.11 scripts/test.py vigenere.cpp

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const size_t ALPHABET_SIZE = 26;

class VigenereCipher {
  private:
    // Private data members
    string mKey;
    char mTable[ALPHABET_SIZE][ALPHABET_SIZE];

    // Private methods
    string makeKeystream(const string message) const;

    // Private helper functions
    static string fileToString(const string inputFile);
    static void stringToFile(const string message, const string outputFile);

  public:
    // Public methods
    VigenereCipher(const string key); // Constructor
    void encrypt(const string inputFile, const string outputFile) const;
    void decrypt(const string inputFile, const string outputFile) const;
    void print() const;
};

// Read the message file into a string
string VigenereCipher::fileToString(const string inputFile) {
    ifstream fin(inputFile);
    string message;
    char character;

    if (!fin.is_open()) {
        cerr << "file " << inputFile << " unable to open." << endl;
        exit(1);
    }

    while (fin.get(character)) {
        message.push_back(character);
    }

    fin.close();

    return message;
}

// Write the message string into a file
void VigenereCipher::stringToFile(const string message,
                                  const string outputFile) {
    ofstream fout(outputFile);

    if (!fout.is_open()) {
        cerr << "output file " << outputFile << " unable to open." << endl;
        exit(1);
    }

    fout << message;

    fout.close();
}

void VigenereCipher::print() const {
    // Printing debug information to `cerr`
    cerr << "Key: " << mKey << endl;
    cerr << "Table:" << endl;
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        for (size_t j = 0; j < ALPHABET_SIZE; j++) {
            cerr << " " << mTable[i][j] << " ";
        }
        cerr << endl;
    }
}

string VigenereCipher::makeKeystream(const string message) const {
    // Since we do not encode special characters, the keystream includes
    // those.
    // For example a message of "good morning!" with a key of "lemon"
    // gives you a keystream of "lemo nlemonl!"
    // Notice the key is continued after the space and no letters of the key are
    // skipped.

    string keystream;
    size_t keyIndex = 0; // Keep track of the next character in the key to use

    for (size_t i = 0; i < message.size(); i++) {
        if (islower(message[i])) {
            // TODO: add a character from the key (mKey) to the keystream
        } else {
            // Add the special character to the keystream
            keystream += message[i];
        }
    }

    cout << "Keystream: " << keystream << endl;

    return keystream;
}

void VigenereCipher::encrypt(const string inputFile,
                             const string outputFile) const {
    // - Read the input file into a string
    // - Create the keystream using the `makeKeystream` function
    // - Encrypt the message with the keystream and Vigenere table
    // - Write the encrypted message to the output file
    // - Use the same `for if islower else` loop as in `makeKeystream`
    const string message = fileToString(inputFile);
    const string keystream = makeKeystream(message);
}

void VigenereCipher::decrypt(const string inputFile,
                             const string outputFile) const {
    // - Read the input file into a string
    // - Create the keystream using the `makeKeystream` function
    // - Decrypt the message with the keystream and Vigenere table
    // - Write the decrypted message to the output file
    // - Use the same `for if islower else` loop as in `makeKeystream`
}

// Constructor
VigenereCipher::VigenereCipher(const string key) {
    // - Store the key into `mKey`
    // - Initialize `mTable`
    // - Use the same for loops as `VigenereCipher::print`
    //   to initialize `mTable`

    // NOTE: Since `mKey` and `mTable` are private, they accesible in any
    // function prefixed with `VigenereCipher::` but not anywhere else,
    // namely `main`.
}

int main(int argc, char **argv) {
    // - Check argc
    // - Usage error message: "usage: ./vigenere inputFile outputFile key [e/d]"
    // - store your four arguments: input file, output file, key, and operation
    // - Construct the VigenereCipher class
    // - Call the appropriate function based on the operation

    // HINT: recommended order: main, VigenereCipher (constructor),
    // makeKeystream, encrypt, decrypt

    const string inputFile /* = TODO */;
    const string outputFile /* = TODO */;
    const string key /* = TODO */;
    const string operation /* = TODO */;

    VigenereCipher cipher(key);

    cipher.print(); // Remove later

    return 0;
}