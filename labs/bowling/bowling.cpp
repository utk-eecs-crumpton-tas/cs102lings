/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

// NOTE:
// `size_t` is an unsigned integer type that is guaranteed to be large
// and is used for representing sizes and indexes
//
// vector `.size()` returns a `size_t` integer value
// compiler warnings happen if you try to compare integer types that do not
// match e.g. `int` and `size_t`

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//! Remember: non-const globals are a penalty
//    "non-const globals" aka variables defined outside of a function e.g. main
//    without the const keyword are a penalty on your grade
const size_t NUMBER_OF_FRAMES = 10;
const size_t ROLLS_PER_FRAME = 2;
const size_t TOTAL_ROLLS = NUMBER_OF_FRAMES * 2 + 1; // 21
const int NUMBER_OF_PINS = 10;

// Use for debugging
void printPlayerRolls(const vector<int> &playerRolls) {
  for (size_t i = 0; i < playerRolls.size(); ++i) {
    cerr << playerRolls[i] << " ";
  }
  cerr << endl;
}

vector<int> inputPlayerRolls() {
  // - handle the first 20 rolls at the last roll separately
  // - Use `[]` to set the values, do not use `push_back`
  // - The vector is filled with zeros by default so you do not need to
  //   manually assign zeros to the vector when there is no rollInput
  vector<int> playerRolls(TOTAL_ROLLS, 0);
  int rollInput;

  // input first 20 rolls
  for (size_t frame = 0; frame < NUMBER_OF_FRAMES; ++frame) {
    for (size_t roll = 0; roll < ROLLS_PER_FRAME; ++roll) {
      // TODO: set prompt e.g. "Enter score for frame 1, roll 1: "
      cin >> rollInput;
      // TODO: if roll is a strike, break out of the inner loop
      // TODO: calculate the rollIndex 0..20 for the current frame and roll
    }
  }

  // if there is a strike or spare on the last frame, prompt for a 3rd roll on
  // the last frame

  // TODO: input the last roll if needed

  return playerRolls;
}

int calculatePlayerScore(const vector<int> &rolls) {
  int roundScore = 0;

  // calculate the first 9 frames
  // - spare = add next frame roll1
  // - strike = add next frame roll1 + roll2
  // - double strike = add next frame roll1 + next next frame roll1
  // - edge case: if there is a double strike on 9 and 10, treat 9 like a normal
  //   strike
  for (size_t frameNumber = 0; frameNumber < NUMBER_OF_FRAMES - 1;
       ++frameNumber) {
    // advice: use a lot of intermediate variables
    const size_t currentFrame = frameNumber * 2;
    const size_t nextFrame = currentFrame + 2;
    const size_t nextNextFrame = nextFrame + 2;

    const int roll1 = rolls[currentFrame];
    const int roll2 = rolls[currentFrame + 1];

    const bool isStrike = roll1 == NUMBER_OF_PINS;
    const bool isSpare = roll1 + roll2 == NUMBER_OF_PINS;

    // TODO: calculate the frame score
  }

  // TODO
  // calculate the 10th frame
  // - strike or a spare = add all three rolls
  // - normal = add the first two rolls

  // HINT: no if/else statements are needed, remember if no roll has no
  // input, it is a zero

  return roundScore;
}

void printGameSummary(const vector<string> &playerNames,
                      const vector<int> &playerScores) {

  // This line prevents the program from seg faulting if no players were entered
  if (playerNames.size() == 0) {
    cout << "No players were entered." << endl;
    return;
  }

  // NOTE: there is a newline between the inputs and the summary,
  // but there is no newline if no players were entered
  cout << endl;

  // TODO: print all players and their scores
  /*
   * "John scored 300."
   * "Cheryl scored 122."
   */

  string worstPlayerName = playerNames[0];
  int worstPlayerScore = playerScores[0];

  string bestPlayerName = playerNames[0];
  int bestPlayerScore = playerScores[0];

  for (size_t i = 1; i < playerNames.size(); ++i) {
    // TODO: find the best and worst score
  }

  // TODO: print results
  /*
   * "Cheryl did the worst by scoring 122."
   * "John won the game by scoring 300."
   */
}

int main() {
  vector<string> playerNames;
  vector<int> playerScores;

  while (true) {
    string inputString;

    cout << "Enter player's name (done for no more players): ";
    cin >> inputString;

    if (inputString == "done") {
      // NOTE: Don't do any of the summary here, exit the loop first
      break;
    }

    const vector<int> playerRolls = inputPlayerRolls();

    const int roundScore = calculatePlayerScore(playerRolls);

    // TODO: store the name and score

    // Prevents infinite loop if cin is in a bad state
    if (!cin) {
      throw runtime_error("Invalid input");
    }
  }

  printGameSummary(playerNames, playerScores);

  return 0;
}