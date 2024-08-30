# CS102lings

Labs templates and tests for UTK CS102

Inspired by [rustlings](https://github.com/rust-lang/rustlings) and [ziglings](https://github.com/ratfactor/ziglings)

## Table of Contents

- [CS102lings](#cs102lings)
  - [Table of Contents](#table-of-contents)
  - [Setup](#setup)
  - [Updating](#updating)
  - [Writing Assignments and Running the Tests](#writing-assignments-and-running-the-tests)
  - [How the Tests are Structured](#how-the-tests-are-structured)
  - [Test Output Examples (and Symbols Meaning)](#test-output-examples-and-symbols-meaning)
    - [Mismatched line `|`](#mismatched-line-)
    - [Missing line `<`](#missing-line-)
    - [Extra line `>`](#extra-line-)
    - [Missing terminating newline `/`](#missing-terminating-newline-)
    - [Extra terminating newline `\`](#extra-terminating-newline-)
  - [Viewing Test Input](#viewing-test-input)
  - [Debugging with the Script](#debugging-with-the-script)
    - [Using print statements](#using-print-statements)
    - [Using `GDB`](#using-gdb)

## Setup

Run the following command to clone the repository:

```bash
git clone https://github.com/utk-eecs-crumpton-tas/cs102lings.git ~/cs102lings
```

You should now have a directory called `cs102lings` verify it with `ls ~`

Change into `~/cs102lings/labs` with `cd ~/cs102lings/labs` and run `ls` to see the labs.

This directory will contain templates for all the labs in this course as well as tests to verify your solutions.

## Updating

To check if the cs102lings repository has been updated, run the following command:

```bash
git status
```

If it prints the following everything is up to date:

```txt
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

If it prints something like this, there is an update:

```txt
On branch main
Your branch is behind 'origin/main' by 1 commit, and can be fast-forwarded.
  (use "git pull" to update your local branch)

nothing to commit, working tree clean
```

To update run:

```bash
git pull
```

When pulling it updated successfully if it prints something like this

```txt
Updating 1a2b3c4..5e6f7g8

Fast-forward
 README.md | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

It was not able to pull changes if it printed something like this

```txt
error: Your local changes to the following files would be overwritten by merge:
  README.md
Please commit your changes or stash them before you merge.
Aborting
```

> **Warning**
> Do not try to fix this on your own, ask for help from a TA.

## Writing Assignments and Running the Tests

Initialize the test with the following command

```bash
make <name-of-test>
# for example
make penname
```

This will create the directory for your project, in `student/penname/`. In this directory you will find `penname.cpp`, this is the file you will edit.

To run the tests for your program, run the following command:

> **Note**
> The script will recompile your program each time you run it, so you don't need to recompile it yourself.
> The tests will create a file in your directory called `lab.bin` which is your compiled program.


```bash
./test.sh <name-of-test>
# example
./test.sh penname
```

## How the Tests are Structured

The tests have several components they will check depending on the lab.

Output components

- `stderr` expects output written to `cerr`
- `stdout` expects output written to `cout`
- `fout` expects output written to an `ofstream`
- `leak-check` checks for memory leaks with `valgrind` (This will not work on Macs)

Input components

- `stdin` provides input to `cin`
- `fin` provides input to an `ifstream`
- `arguments` the command line arguments that will be passed to the input program

All files associated with a test can be found in `tests/TEST_NAME/` e.g. `tests/001-absolute-value-operator/`

## Test Output Examples (and Symbols Meaning)

The tests use the `diff -y` command to compare your output to the tests. the `|` symbol means the two lines are different. The `>` symbol with output in green means the line is extra in your program. The `<` symbol with output in red means the line is missing is yours.

### Mismatched line `|`

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:

Your penname name is Birmingham Johnson.                      | Your penname is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                                Your address is 59 Student Lane.
```

on this line from above `name` is missing

```txt
Your penname name is Birmingham Johnson.                      | Your penname is Birmingham Johnson.
```

If the lines look the same, then it could be a whitespace issue (space or newline character).

### Missing line `<`

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:
                                                              <
Your penname name is Birmingham Johnson.                        Your penname name is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                                Your address is 59 Student Lane.
```

This (typically red) arrow, means a line is missing between the two.

```txt
Enter your city of birth:                                       Enter your city of birth:
                                                              <
Your penname name is Birmingham Johnson.                        Your penname name is Birmingham Johnson.
```

### Extra line `>`

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
                                                              >
Enter your age:                                                 Enter your age:
                                                              >
Enter your street number, name, and type:                       Enter your street number, name, and type:
                                                              >
Enter your city of birth:                                       Enter your city of birth:
                                                              >

Your penname name is Birmingham Johnson.                        Your penname name is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                                Your address is 59 Student Lane.
```

This (typically green) arrows, mean your program is printing an extra line.

### Missing terminating newline `/`

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:

Your penname name is Birmingham Johnson.                        Your penname name is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                              / Your address is 59 Student Lane.
```

```txt
Your address is 59 Student Lane.                              / Your address is 59 Student Lane.
```

The `/` means your output is missing a newline at the end.

### Extra terminating newline `\`

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:

Your penname name is Birmingham Johnson.                        Your penname name is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                              \ Your address is 59 Student Lane.
```

```txt
Your address is 59 Student Lane.                              \ Your address is 59 Student Lane.
```

The `\` means your output has a newline at the end and the solution does not.

## Viewing Test Input

Run the tests with the `--print` flag. This will print the `stdin` or `fin` for the failed test if any exists.

```bash
python3.11 scripts/test.py penname.cpp --print
```

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:

Your penname name is Birmingham Johnson.                      | Your penname is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                                Your address is 59 Student Lane.

your stderr
cat tests/001-canvas/stderr.tmp.txt
Debug informatoin!

command
./lab.bin  < tests/001-canvas/stdin.txt

stdin
cat tests/001-canvas/stdin.txt
Johnathan Student
31
222 Johnson Lane
Birmingham
```

This is the `stdin` component printed for this test.

```txt
stdin
cat tests/001-canvas/stdin.txt
Johnathan Student
31
222 Johnson Lane
Birmingham
```

## Debugging with the Script

### Using print statements

Most of the time, you should be able to print debug information to `cerr`. The scripts will automatically print anything written to `cerr` if it detects anything.

Debug statement:

```cpp
cerr << "Debug information!" << endl;
```

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:

Your penname name is Birmingham Johnson.                      | Your penname is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                                Your address is 59 Student Lane.

your stderr
cat tests/001-canvas/stderr.tmp.txt
Debug informatoin!
```

Noticed the `Debug information!` line in the `your stderr` section.

### Using `GDB`

The scripts include a debug option you can invoke with the `--debug` flag

```bash
python3.11 scripts/test.py penname.cpp --debug
```

```txt
(1/13)  canvas
  stdout     failed

expected                                                        yours
Enter your first and middle names:                              Enter your first and middle names:
Enter your age:                                                 Enter your age:
Enter your street number, name, and type:                       Enter your street number, name, and type:
Enter your city of birth:                                       Enter your city of birth:

Your penname name is Birmingham Johnson.                      | Your penname is Birmingham Johnson.
You will write as a 15 year old.                                You will write as a 15 year old.
Your address is 59 Student Lane.                                Your address is 59 Student Lane.

command
./lab.bin  < tests/001-canvas/stdin.txt

To view the test input run with the print flag
python3.11 scripts/test.py source_file --print

debug: break
Pausing execution at the start of the program

q|quit to exit
b|break to set a breakpoint
c|continue to resume execution normally
n|next to go to the next line, skipping function calls
s|step to go to the next line, entering function calls
fin|finish to return from the current function
l|list to print the next 10 lines
p|print [variable] to print a variable
bt|backtrace to print the previous function calls
h|help [command] print help or help for a command
enter to repeat the previous command

GNU gdb (GDB) Fedora Linux 13.2-6.fc38
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from lab.bin...
Breakpoint 1 at 0x4011d2: file penname.cpp, line 6.
Starting program: lab.bin < tests/001-canvas/stdin.txt

Thread debugging using libthread_db enabled
Using host libthread_db library "/lib64/libthread_db.so.1".

Breakpoint 1, main () at penname-gradescript-example.cpp:6
6           string first_name;
(gdb)
```

This will attach an interactive gdb instance you can use to inspect and step through your program.
