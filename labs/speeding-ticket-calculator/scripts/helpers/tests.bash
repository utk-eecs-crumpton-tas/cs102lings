test_exit_status() {
    local exit_status="$1"
    local tmp_exit_status="$2"
    # Should succeed: Error
    if (($exit_status == 0 && $tmp_exit_status != 0)); then
        echo -e "${ERROR_STYLE}Error:${RESET}" >&2
        echo -e "  Received unexpected non-zero exit status: ${CODE_STYLE}$tmp_exit_status${RESET}" >&2
        echo
        return 1
    fi

    # Should fail: Warning
    if (($exit_status != 0 && $tmp_exit_status == 0)); then
        echo -e "${WARNING_STYLE}Warning:${RESET}" >&2
        echo -e "  Expected non-zero exit status" >&2
        echo
        return 0
    fi

    return 0
}

split_line_on() {
    local pattern="$1"
    if [[ "$pattern" != '' ]]; then
        sed -E "s/$pattern/&\n/g"
    else
        cat
    fi
}

test_output() {
    # Test
    local solution_path="$1"
    local tmp_path="$2"
    local exit_status_path="$3"
    local test_type="$4"
    # Options
    local is_verbose="$5"
    local diff_color="$6"
    local pattern="$7"

    if ! [[ -f "$solution_path" ]]; then
        return
    fi

    if ! [[ -f "$tmp_path" ]]; then
        echo -e "${ERROR_STYLE}Error:${RESET} expected output file" >&2
        echo -e "  ${CODE_STYLE}$tmp_path${RESET}" >&2
        echo -e "  does not exist" >&2
        return 1
    fi

    local is_passed=$(if
        # cmp -s "$solution_path" "$tmp_path"
        diff "$solution_path" "$tmp_path" >/dev/null
    then
        echo -n true
    else
        echo -n false
    fi)

    local is_failed=$(if ! $is_passed; then echo -n true; else echo -n false; fi)

    if "$is_passed"; then
        printf "  ${TEST_SUBHEADER_STYLE}%-10s${RESET} ${TEST_SUCCESS_STYLE}passed${RESET}\n" "$test_type"
    else
        printf "  ${TEST_SUBHEADER_STYLE}%-10s${RESET} ${TEST_FAILURE_STYLE}failed${RESET}\n" "$test_type"
    fi

    # Test report
    if "$is_failed" || "$is_verbose"; then
        echo

        printf "${TEST_REPORT_STYLE}%-64s%s${RESET}\n" expected yours
        diff -y "$diff_color" \
            <(cat "$solution_path" | split_line_on "$pattern") \
            <(cat "$tmp_path" | split_line_on "$pattern")
        echo
    fi

    if "$is_passed"; then
        return 0
    else
        return 1
    fi

}

test_leak_check() {
    # Test
    local command_with_args="$1"
    local tmp_stdin_path="$2"
    local report_file="$3"
    local exit_status="$4"
    local tmp_exit_status="$5"
    # Options
    local is_leak_check="$6"
    local is_skip_leak_check="$7"
    local is_verbose="$8"

    local test_type=leak-check

    if ! $is_leak_check || $is_skip_leak_check; then
        return
    fi

    if ! command -v valgrind >/dev/null; then
        echo -e "${ERROR_STYLE}Error:${RESET}" >&2
        echo -e "  ${CODE_STYLE}valgrind${RESET} is not installed" >&2
        exit 1
    fi

    # Skip leak check if program should error
    if (($exit_status != 0)); then
        return 0
    fi

    if (($tmp_exit_status != 0)); then
        echo -e "${ERROR_STYLE}Error:${RESET} skipping leak check because of non-zero exit status" >&2
        return 1
    fi

    local stdin=$([[ -f "$tmp_stdin_path" ]] && cat "$tmp_stdin_path")

    local is_passed=$(if
        valgrind \
            --leak-check=full \
            --error-exitcode=1 \
            -- \
            $command_with_args \
            <<<"$stdin" \
            >/dev/null \
            2>"$report_file"
    then
        echo -n true
    else
        echo -n false
    fi)

    local is_failed=$(if ! $is_passed; then echo -n true; else echo -n false; fi)

    if "$is_passed"; then
        printf "  ${TEST_SUBHEADER_STYLE}%-10s${RESET} ${TEST_SUCCESS_STYLE}passed${RESET}\n" "$test_type"
    else
        printf "  ${TEST_SUBHEADER_STYLE}%-10s${RESET} ${TEST_FAILURE_STYLE}failed${RESET}\n" "$test_type"
    fi

    # Test report
    if "$is_failed" || "$is_verbose"; then
        echo

        echo -e "${TEST_REPORT_STYLE}report${RESET}"
        cat "$report_file"
        echo
    fi

    if "$is_passed"; then
        return 0
    else
        return 1
    fi

}

print_file() {
    local name="$1"
    local path="$2"
    if ! [[ -f "$path" && -s "$path" ]]; then
        return
    fi

    echo -e "${TEST_INFO_STYLE}${name}${RESET}"
    echo -e "${CODE_STYLE}cat ${path}${RESET}"
    echo -e "$(cat "$path")"
    echo
}

print_test_summary() {
    local print_test_info="${1}"
    local command_with_args="${2}"
    local tmp_stdin_path="${3}"
    local tmp_stdout_path="${4}"
    local tmp_stderr_path="${5}"
    local fin_path="${6}"
    local tmp_fout_path="${7}"
    local hint_path="${8}"
    local pattern="${9}"

    if [[ -f "$hint_path" ]]; then
        echo -e "${TEST_INFO_STYLE}hint${RESET}"
        print_file "$hint_path"
        echo
    fi

    local stdin=$(if [[ -f "$tmp_stdin_path" ]]; then
        echo -n " <$tmp_stdin_path"
    fi)

    echo -e "${TEST_INFO_STYLE}run with${RESET}"
    echo -e "${CODE_STYLE}$command_with_args$stdin${RESET}"
    echo

    if [[ "$print_test_info" == 'none' ]]; then
        echo -e "${TEST_INFO_STYLE}For more info run with the print flag:${RESET}"
        echo -e "${CODE_STYLE}bash $0 <source-file> --print [input|output|all]${RESET}"
        return
    fi

    if [[ "$print_test_info" == 'input' || "$print_test_info" == 'all' ]]; then
        print_file 'stdin' "$tmp_stdin_path"
        print_file 'fin' "$fin_path"
    fi

    if [[ "$print_test_info" == 'output' || "$print_test_info" == 'all' ]]; then
        print_file 'your stdout' "$tmp_stdout_path" | split_line_on "$pattern"
        print_file 'your stderr' "$tmp_stderr_path"
        print_file 'your fout' "$tmp_fout_path"
    fi

}
