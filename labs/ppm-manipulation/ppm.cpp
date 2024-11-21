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
//  - gradescript command: python3.11 scripts/test.py ppm.cpp

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Pixel {
    uint red;
    uint green;
    uint blue;
};

class Picture {
  private:
    size_t width;
    size_t height;
    uint maxIntensity;
    vector<Pixel> pixels;

    // Mutator
    Pixel &getPixel(const size_t row, const size_t column);

    // Accessor
    const Pixel &getPixel(const size_t row, const size_t column) const;

    void setPixel(const size_t row, const size_t column, const Pixel &pixel);

  public:
    Picture();

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

void Picture::writeOutput(ostream &out) {
    out << "P3" << '\n'
        << width << ' ' << height << '\n'
        << maxIntensity << '\n';

    for (size_t y = 0; y < height; ++y) {
        out << '\n';
        out << "# Row " << y << '\n';
        for (size_t x = 0; x < width; ++x) {
            if (x != 0) {
                out << (x % 4 != 0 ? "   " : "\n");
            }
            const Pixel &pixel = getPixel(x, y);
            out << setw(3) << pixel.red << ' ' << setw(3) << pixel.green << ' '
                << setw(3) << pixel.blue;
        }
        out << '\n';
    }
}

// TODO: Implement the rest of the Picture class

bool Picture::readInput(istream &in) {
    // - Call `getline` once to check `"P3"`
    // - Create a stringstream: `stringstream inWithoutComments;`
    // - Do while `getline` to get all the lines out of your input and
    //   check if the lines are not empty and start with `'#'`
    //   then you can do
    //     `inWithoutComments << line << '\n`
    //   for all the lines that are not comments
    // - Then all that's in your `inWithoutComments` is the numbers
    //   separated by whitespace
    // - Then after that you can simply use the extraction operator on the
    //   `stringstream`, `inWithoutComments`, to read in all the numbers
    // - Read out the `width`, `height`, and `maxIntensity`
    // - Create a `vector` and use `width` and `height` to resize your vector
    // - Use a for loop to read in all the pixels
    // - Check if any of the rgb color values exceed the `maxIntensity`

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
    //   except using cout for a dash (-) and ofstream for a filename
    return 0;
}