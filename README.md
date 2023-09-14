# CS102lings

Course materials for UTK cs102

Inspired by:

- [rustlings](https://github.com/rust-lang/rustlings)
- [ziglings](https://github.com/ratfactor/ziglings)

## Setup

Run the following command to clone the repository:

```bash
git clone https://github.com/utk-eecs-crumpton-tas/cs102lings.git
```

You should now have a directory called `cs102lings` verify with `ls`

Change into `cs102lings/labs` with `cd cs102lings/labs` and run `ls` to see the labs.

This directory will contain templates for all the labs in this course as well as tests to verify your solutions.

## Usage

Change into the directory of the lab, for example penname.

```bash
cd cs102lings/labs/panname
```

`panname.cpp` is the template for the lab. Write your program here.

To run the tests for your program, run the following command:

> :note:
> The script will recompile your program each time you run it, so you don't need to recompile it yourself.
> The gradescript will create a file in your directory called `lab.bin` which is your compiled program.

```bash
bash scripts/test.bash panname.cpp
```

## About the Gradescripts

The gradescripts have several components they will check depending on the lab.

Output components

- `stderr` expects output written to `cerr`
- `stdout` expects output written to `cout`
- `fout` expects output written to an `ofstream`
- `leak-check` checks for memory leaks with `valgrind` (This will not work on Macs)

Input components

- `stdin` provides input to `cin`
- `fin` provides input to `ifstream`

All files associated with a test can be found in `tests/TEST_NAME/` e.g. `tests/001-absolute-value-operator/`

## Examples

The tests use the `diff` command to compare your output to the tests. the `|` symbol means the two lines are different. The `>` symbol with output in green means the line is extra in your program. The `<` symbol with output in red means the line is missing is yours. If the lines look the same, then it could be a whitespace issue.

### Mismathced line line `|`

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

run with
./lab.bin <tests/001-canvas/stdin.tmp.txt

For more info run with the print flag:
bash scripts/test.bash <source-file> --print [input|output|all]
```

on this line from above `name` is missing

```txt
Your penname name is Birmingham Johnson.                      | Your penname is Birmingham Johnson.
```

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

run with
./lab.bin <tests/001-canvas/stdin.tmp.txt

For more info run with the print flag:
bash scripts/test.bash <source-file> --print [input|output|all]
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

run with
./lab.bin <tests/001-canvas/stdin.tmp.txt

For more info run with the print flag:
bash scripts/test.bash <source-file> --print [input|output|all]
```

This (typically green) arrows, mean your program is printing an extra line.

### Missing terminating newline `\`

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

run with
./lab.bin <tests/001-canvas/stdin.tmp.txt

For more info run with the print flag:
bash scripts/test.bash <source-file> --print [input|output|all]
```

```txt
Your address is 59 Student Lane.                              / Your address is 59 Student Lane.
```

The `/` means your output is missing a newline at the end.

## Showing more output

Run the tests with the `--print` flag. Valid options are `input`, 'output`, and `all`.

`input` will print the `stdin` and `fin` components

`output` will print the `stdout`, `stderr`, and `fout` components

`all` will print all components

```bash
bash scripts/test.bash panname.cpp --print all
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

run with
./lab.bin <tests/001-canvas/stdin.tmp.txt

stdin
cat tests/001-canvas/stdin.tmp.txt
Johnathan Student
31
222 Johnson Lane
Birmingham

your stdout
cat tests/001-canvas/stdout.tmp.txt
Enter your first and middle names:
Enter your age:
Enter your street number, name, and type:
Enter your city of birth:

Your penname is Birmingham Johnson.
You will write as a 15 year old.
Your address is 59 Student Lane.

your stderr
cat tests/001-canvas/stderr.tmp.txt
```

## Debugging

Most of the time, you should be able to print debug information to `cerr` and inspect it with `--print output`.

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

run with
./lab.bin <tests/001-canvas/stdin.tmp.txt

stdin
cat tests/001-canvas/stdin.tmp.txt
Johnathan Student
31
222 Johnson Lane
Birmingham

your stdout
cat tests/001-canvas/stdout.tmp.txt
Enter your first and middle names:
Enter your age:
Enter your street number, name, and type:
Enter your city of birth:

Your penname is Birmingham Johnson.
You will write as a 15 year old.
Your address is 59 Student Lane.

your stderr
cat tests/001-canvas/stderr.tmp.txt
Debug informatoin!
```

Noticed the `Debug information!` line in the `stderr` section.

You can see how the lab was run and run by itself under the run with section:

```bash
./lab.bin <tests/001-canvas/stdin.tmp.txt
```

Copy, paste, and run this section into the command line to run the test by itself.
