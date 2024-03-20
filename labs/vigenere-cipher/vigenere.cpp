/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

const size_t ALPHABET_SIZE = 26;

class VigenereCipher {
  private:
    string mKey;
    char mVTable[ALPHABET_SIZE][ALPHABET_SIZE];
    string fileToString(const string inputFile) const;
    void stringToFile(const string message, const string outputFile) const;
    string makeKeystream(const string message) const;

  public:
    VigenereCipher(const string key);
    void encrypt(const string inputFile, const string outputFile) const;
    void decrypt(const string inputFile, const string outputFile) const;
    void printVTable() const;
};

string VigenereCipher::fileToString(const string inputFile) const {
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

void VigenereCipher::stringToFile(const string message,
                                  const string outputFile) const {
    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cerr << "output file " << outputFile << " unable to open." << endl;
        exit(1);
    }
    fout << message;
    fout.close();
}

string VigenereCipher::makeKeystream(const string message) const {
    /* Extra note/reminder about keystreams - since we don't encode special
      characters, the keystream includes those. For example, a message of "good
      morning" with a key of "lemon" gives you a keystream of "lemo nlemone" */
}

VigenereCipher::VigenereCipher(const string key) {}

void VigenereCipher::encrypt(const string inputFile,
                             const string outputFile) const {}

void VigenereCipher::decrypt(const string inputFile,
                             const string outputFile) const {}

void VigenereCipher::printVTable() const {
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        for (size_t j = 0; j < ALPHABET_SIZE; j++) {
            cout << " " << mVTable[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {

    // VigenereCipher cipher(key);
}