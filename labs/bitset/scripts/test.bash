SCRIPTS_DIR='scripts'
TESTS_DIR='tests'
if ! [[ -d "$SCRIPTS_DIR" && -d "$TESTS_DIR" ]]; then
    echo "Usage: scripts/test.bash <source-file>" >&2
    echo "This script must be run from the root directory of the project" >&2
    exit 1
fi

. "$SCRIPTS_DIR/env/variables.bash"
. "$SCRIPTS_DIR/env/colors.bash"
for SRC in "$SCRIPTS_DIR"/helpers/*.bash; do
    . "$SRC"
done

usage() {
    echo "Usage: bash $0 <source-file>"
    echo
    echo 'Options:'
    echo '  --help                      Display this message'
    echo '  --clean                     Clean up temporary files'
    echo '  --verbose                   Display test summary for passed tests'
    echo '  --no-diff-color             Disable colored diff output'
    echo '  --skip-leak-check           Disable valgrind leak check'
    echo '  --no-exit-on-fail           Continue running tests after a failure'
    echo '  --print [input|output|all]  Print additional test summary info'
}

FLAGS=("${@:1}")

IS_HELP=$(parse_flag "${FLAGS[*]}" '--help') || exit 1
IS_CLEAN=$(parse_flag "${FLAGS[*]}" '--clean') || exit 1
IS_VERBOSE=$(parse_flag "${FLAGS[*]}" '--verbose') || exit 1
IS_NO_DIFF_COLOR=$(parse_flag "${FLAGS[*]}" '--no-diff-color') || exit 1
IS_SKIP_LEAK_CHECK=$(parse_flag "${FLAGS[*]}" '--skip-leak-check') || exit 1
IS_NO_EXIT_ON_FAIL=$(parse_flag "${FLAGS[*]}" '--no-exit-on-fail') || exit 1
PRINT_TEST_INFO=$(parse_flag "${FLAGS[*]}" '--print' 'input output all') || exit 1

# Derived flags
IS_EXIT_ON_FAIL=$("$IS_NO_EXIT_ON_FAIL" && echo -n false || echo -n true)
DIFF_COLOR_ARG=$("$IS_NO_DIFF_COLOR" || echo -n '--color')

# Test variables
SRC_FILE="$1"
BIN_FILE='lab.bin'

if ! [[ -d "$TESTS_DIR" ]]; then
    echo -e "${ERROR_STYLE}Tests directory not found${RESET}" >&2
    exit 1
fi
TESTS=($(ls "$TESTS_DIR"))

# Help
if "$IS_HELP"; then
    usage
    exit
fi

# Clean
rm -f "$BIN_FILE"
rm -f "$TESTS_DIR"/*/*.tmp.txt

if "$IS_CLEAN"; then
    echo "Cleaning up temporary testing files..."
    exit
fi

# Build
if [[ "$SRC_FILE" == '' ]]; then
    echo -e "${ERROR_STYLE}Source file not specified${RESET}" >&2
    usage
    exit 1
fi

if ! [[ -f "$SRC_FILE" ]]; then
    echo -e "${ERROR_STYLE}Source file not found${RESET}" >&2
    usage
    exit 1
fi

if ! g++ -std=c++11 -Wall -o "$BIN_FILE" "$SRC_FILE"; then
    echo -e "${ERROR_STYLE}Build failed${RESET}" >&2
    exit 2
fi

NUMBER_TESTS="${#TESTS[@]}"
test_number=1

# Run
for TEST_NAME in "${TESTS[@]}"; do
    SHORT_TEST_NAME="${TEST_NAME#*-}"
    printf "${YELLOW}%-7s${RESET} ${TEST_HEADER_STYLE}%s${RESET}\n" "($test_number/$NUMBER_TESTS)" "$SHORT_TEST_NAME"
    TEST_DIR="$TESTS_DIR/$TEST_NAME"

    ARGUMENTS_PATH="$TEST_DIR/arguments.txt"
    STDIN_PATH="$TEST_DIR/stdin.txt"

    STDOUT_PATH="$TEST_DIR/stdout.txt"
    STDERR_PATH="$TEST_DIR/stderr.txt"

    FIN_PATH="$TEST_DIR/fin.txt"
    FOUT_PATH="$TEST_DIR/fout.txt"

    EXIT_STATUS_PATH="$TEST_DIR/exit-status.txt"

    HINT_PATH="$TEST_DIR/hint.txt"

    # Tmp files
    TMP_ARGUMENTS_PATH="$TEST_DIR/arguments.tmp.txt"
    TMP_STDIN_PATH="$TEST_DIR/stdin.tmp.txt"
    TMP_STDOUT_PATH="$TEST_DIR/stdout.tmp.txt"
    TMP_STDERR_PATH="$TEST_DIR/stderr.tmp.txt"

    TMP_FOUT_PATH="$TEST_DIR/fout.tmp.txt"

    # TMP_EXIT_STATUS_PATH="$TEST_DIR/exit-status.tmp.txt"

    TMP_LEAK_REPORT_PATH="$TEST_DIR/leak-summary.tmp.txt"

    ARGUMENTS=$(
        read_and_substitute_input \
            "$ARGUMENTS_PATH" \
            "$TMP_ARGUMENTS_PATH" \
            "$FIN_PATH" \
            "$TMP_FOUT_PATH"
    )
    STDIN=$(
        read_and_substitute_input \
            "$STDIN_PATH" \
            "$TMP_STDIN_PATH" \
            "$FIN_PATH" \
            "$TMP_FOUT_PATH"
    )

    COMMAND_WITH_ARGS=$(if [[ "$ARGUMENTS" == '' ]]; then
        echo -n "./$BIN_FILE"
    else
        echo -n "./$BIN_FILE $ARGUMENTS"
    fi)

    $COMMAND_WITH_ARGS <<<"$STDIN" 1>"$TMP_STDOUT_PATH" 2>"$TMP_STDERR_PATH"

    TMP_EXIT_STATUS="$?"
    EXIT_STATUS=$(cat "$EXIT_STATUS_PATH")

    is_failed=false

    if ! test_exit_status \
        "$EXIT_STATUS" \
        "$TMP_EXIT_STATUS" \
        "$TMP_STDERR_PATH" \
        ; then
        is_failed="$IS_EXIT_ON_FAIL"
    fi

    if ! "$is_failed" && ! test_output \
        "$STDOUT_PATH" \
        "$TMP_STDOUT_PATH" \
        "$EXIT_STATUS_PATH" \
        stdout \
        \
        "$IS_VERBOSE" \
        "$DIFF_COLOR_ARG" \
        "$SPLIT_LINE_ON" \
        ; then
        is_failed="$IS_EXIT_ON_FAIL"
    fi

    if ! "$is_failed" && ! test_output \
        "$STDERR_PATH" \
        "$TMP_STDERR_PATH" \
        "$EXIT_STATUS_PATH" \
        stderr \
        \
        "$IS_VERBOSE" \
        "$DIFF_COLOR_ARG" \
        "$SPLIT_LINE_ON" \
        ; then
        is_failed="$IS_EXIT_ON_FAIL"
    fi

    if ! "$is_failed" && ! test_output \
        "$FOUT_PATH" \
        "$TMP_FOUT_PATH" \
        "$EXIT_STATUS_PATH" \
        fout \
        \
        "$IS_VERBOSE" \
        "$DIFF_COLOR_ARG" \
        "$SPLIT_LINE_ON" \
        ; then
        is_failed="$IS_EXIT_ON_FAIL"
    fi

    if ! "$is_failed" && ! test_leak_check \
        "$COMMAND_WITH_ARGS" \
        "$TMP_STDIN_PATH" \
        "$TMP_LEAK_REPORT_PATH" \
        "$EXIT_STATUS" \
        "$TMP_EXIT_STATUS" \
        \
        "$IS_LEAK_CHECK" \
        "$IS_SKIP_LEAK_CHECK" \
        "$IS_VERBOSE" \
        ; then
        is_failed="$IS_EXIT_ON_FAIL"
    fi

    if "$is_failed" || "$IS_VERBOSE"; then
        print_test_summary \
            "$PRINT_TEST_INFO" \
            "$COMMAND_WITH_ARGS" \
            "$TMP_STDIN_PATH" \
            "$TMP_STDOUT_PATH" \
            "$TMP_STDERR_PATH" \
            "$FIN_PATH" \
            "$TMP_FOUT_PATH" \
            "$HINT_PATH" \
            "$SPLIT_LINE_ON"
    fi

    if "$is_failed"; then
        exit 3
    fi

    ((++test_number))

    echo
done

if "$IS_EXIT_ON_FAIL"; then
    echo -e "${ALL_TESTS_PASSED_STYLE}All tests passed${RESET}"
fi
