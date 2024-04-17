/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Pixel {
    // TODO: Implement the Pixel struct
};

class Picture {
  private:
    size_t width;
    size_t height;
    uint maxIntensity;
    vector<Pixel> pixels;

  public:
    Picture();

    const Pixel &getPixel(const size_t row, const size_t column) const;
    Pixel &getPixel(const size_t row, const size_t column);
    void setPixel(const size_t row, const size_t column, const Pixel &pixel);

    void invert();
    void flipY();
    void flipX();

    // istream is a generic interface that works with cin and ifstream
    // - readInput(cin); // ok
    // - readInput(fin); // ok
    bool readInput(istream &in);
    // ostream is a generic interface that works with cout and ofstream
    // - writeOutput(cout); // ok
    // - writeOutput(fout); // ok
    void writeOutput(ostream &out);
};

// TODO: Implement the Picture class

bool Picture::readInput(istream &in) {
    // - Call `getline` once to check `"p3"`
    // - Create a stringstream: `stringstream in_without_comments;`
    // - Do while `getline` to get all the lines out of your input and
    //   check if the lines start with `'#'` then you can do
    //     `in_without_comments << line << '\n`
    //   for all the lines that are not comments
    // - Then all that's in your `in_without_comments` is the numbers
    // - Then after that you can simply use the extraction operator on the
    //   `stringstream`, `in_without_comments`, to read in all the numbers
    // - Read out the `width`, `height`, and `maxIntensity`
    // - Create a `vector` and use `width` and `height` to resize your vector
    // - Use a for loop to read in all the pixels

    return true;
}

int main(int argc, char **argv) {
    // - argc can be 3 or 4, an argc of 3 means no change to the picture
    // - Determine if argv[1] is a dash (-) or not, if it is a dash then pass
    //   cin to read input `readInput(cin);`, otherwise open the file specified
    //   by argv[1]: ifstream fin(argv[1]);
    // - Remember to check if `readInput` returns false
    // - Check if you have an argv[3], if so, determine which operation to
    //   perform: flipX, flipY, invert
    // - Lastly, for the output, handle argv[2] the same way you did for argv[1]
    //   except using cout for a dash (-) and ofstream for a file name
    return 0;
}