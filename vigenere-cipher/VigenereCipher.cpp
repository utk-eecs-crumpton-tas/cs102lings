/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

class VigenereCipher {
private:
  string key;
  char vTable[26][26];
  string fileToString(string fileName);
  void stringToFile(string s, string outputFileName);
  string makeKeystream(string msg);

public:
  VigenereCipher(string k);
  void encrypt(string inputFile, string outputFile);
  void decrypt(string inputFilename, string outputFilename);
  void printVTable();
};

string VigenereCipher::fileToString(string fileName) {
  ifstream fin(fileName);
  string message;
  char character;

  if (!fin.is_open()) {
    cerr << "file " << fileName << " unable to open." << endl;
    exit(1);
  }
  while (fin.get(character)) {
    message.push_back(character);
  }
  fin.close();
  return message;
}

void VigenereCipher::stringToFile(string s, string outputFileName) {
  ofstream fout(outputFileName);
  if (!fout.is_open()) {
    cerr << "output file " << outputFileName << " unable to open." << endl;
    exit(1);
  }
  fout << s;
  fout.close();
}

string VigenereCipher::makeKeystream(string msg) {
  /* Extra note/reminder about keystreams - since we don't encode special
    characters, the keystream includes those. For example, a message of "good
    morning" with a key of "lemon" gives you a keystream of "lemo nlemone" */
}

VigenereCipher::VigenereCipher(string k) {}

void VigenereCipher::encrypt(string inputFile, string outputFile) {}

void VigenereCipher::decrypt(string inputFile, string outputFile) {}

void VigenereCipher::printVTable() {
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      cout << " " << vTable[i][j] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char **argv) {

  // VigenereCipher v(key);
}