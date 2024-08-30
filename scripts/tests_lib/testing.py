import re
from pathlib import Path
from sys import argv
from typing import LiteralString
from .files import read_file, write_file
from .config import ExitCodes, DebugChoice, ScriptConfig
from .shell import (
    shell,
    cat,
    compile_program,
    check_compiler_warning,
    diff,
    diff_y,
    command_exists,
    valgrind,
)
from .formatting import (
    YELLOW,
    CODE_STYLE,
    TEST_HEADER_STYLE,
    TEST_REPORT_STYLE,
    TEST_INFO_STYLE,
    ALL_TESTS_PASSED_STYLE,
    RESET,
    print_missing,
    print_skipped,
    print_warning,
    print_error,
    print_fatal,
    print_result,
)


def run_program(
    command: str,
    timeout_duration: str,
    expected_exit_status: int,
    stdin_path: Path,
    user_stdout_path: Path,
    user_stderr_path: Path,
) -> tuple[bool, int]:
    exit_status = shell(
        command=f"timeout {timeout_duration} {command}",
        stdin_path=stdin_path,
        stdout=user_stdout_path,
        stderr=user_stderr_path,
    )

    if exit_status == ExitCodes.TIMEOUT.value:
        print_error(
            f"timeout: Program runtime exceeded {CODE_STYLE}{timeout_duration}{RESET}",
            "Check for infinite loops or increase the timeout with the --timeout flag",
            f"Example: {CODE_STYLE}--timeout 10s{RESET}",
            end="\n\n",
        )
        return False, exit_status

    is_error = exit_status != 0
    is_expected_error = expected_exit_status != 0

    if is_expected_error and not is_error:
        print_error(
            "Expected non-zero exit status",
            indent=2,
        )
        return False, exit_status

    if not is_expected_error and is_error:
        print_error(
            f"Received unexpected non-zero exit status: {CODE_STYLE}{exit_status}{RESET}",
            indent=2,
        )
        return False, exit_status

    return True, exit_status


def format_output(
    output_path: Path, split_stdout_on: str | None, is_show_whitespaces: bool
):
    """Adds back the newlines removed by piping in stdin"""
    is_split = split_stdout_on is not None and split_stdout_on
    if not is_split and not is_show_whitespaces:
        return output_path

    formatted_output_path = output_path.parent / f"{output_path.stem}.formatted.tmp.txt"

    output = read_file(output_path)

    formatted_output = (
        str(re.sub(split_stdout_on, r"\g<0>\n", output))
        if split_stdout_on is not None and split_stdout_on
        else output
    )

    replaced_output = (
        formatted_output.replace(" ", "·") if is_show_whitespaces else formatted_output
    )

    write_file(formatted_output_path, replaced_output)

    return formatted_output_path


def diff_output(
    component_name: LiteralString,
    solution_output_path: Path,
    user_output_path: Path,
    is_verbose: bool,
    split_stdout_on: str | None,
    is_show_whitespaces: bool,
    is_no_color: bool,
):
    if not solution_output_path.exists():
        if user_output_path.exists():
            print_test_file(f"your {component_name}", user_output_path)
        return True

    if not user_output_path.exists():
        print_missing(component_name)
        print()
        print(f"{TEST_REPORT_STYLE}expected{RESET}")
        cat(solution_output_path)
        print()

        return False

    is_passed = diff(solution_output_path, user_output_path)

    print_result(component_name, is_passed)

    if not is_passed or is_verbose:
        formatted_solution_output_path = format_output(
            output_path=solution_output_path,
            split_stdout_on=split_stdout_on,
            is_show_whitespaces=is_show_whitespaces,
        )
        formatted_user_output_path = format_output(
            output_path=user_output_path,
            split_stdout_on=split_stdout_on,
            is_show_whitespaces=is_show_whitespaces,
        )

        print()
        print(f"{TEST_REPORT_STYLE}{'expected':64}yours{RESET}")

        diff_y(is_no_color, formatted_solution_output_path, formatted_user_output_path)
        print()

    return is_passed


def run_leak_check(
    command: str,
    solution_exit_status: int,
    user_exit_status: int,
    stdin_path: Path,
    user_leak_report_path: Path,
    is_leak_check: bool,
    is_verbose: bool,
):
    if not is_leak_check:
        return True

    if not command_exists("valgrind"):
        print_error(
            f"{CODE_STYLE}valgrind{RESET} is not installed",
            end="\n\n",
        )
        return False

    # valgrind does not work for non-zero exit statuses
    if solution_exit_status != 0:
        return True

    if user_exit_status != 0:
        print_skipped("leak-check")
        print()
        return False

    is_passed = valgrind(command, stdin_path, user_leak_report_path)

    print_result("leak-check", is_passed)

    if not is_passed or is_verbose:
        print()
        cat(user_leak_report_path)
        print()

    return is_passed


def gdb_help():
    print(
        f"{CODE_STYLE}q{RESET}|{CODE_STYLE}quit{RESET} to exit",
        f"{CODE_STYLE}b{RESET}|{CODE_STYLE}break{RESET} to set a breakpoint",
        f"{CODE_STYLE}c{RESET}|{CODE_STYLE}continue{RESET} to resume execution normally",
        f"{CODE_STYLE}n{RESET}|{CODE_STYLE}next{RESET} to go to the next line, skipping function calls",
        f"{CODE_STYLE}s{RESET}|{CODE_STYLE}step{RESET} to go to the next line, entering function calls",
        f"{CODE_STYLE}fin{RESET}|{CODE_STYLE}finish{RESET} to return from the current function",
        f"{CODE_STYLE}l{RESET}|{CODE_STYLE}list{RESET} to print the next 10 lines",
        f"{CODE_STYLE}p{RESET}|{CODE_STYLE}print{RESET} [{CODE_STYLE}variable{RESET}] to print a variable",
        f"{CODE_STYLE}bt{RESET}|{CODE_STYLE}backtrace{RESET} to print the previous function calls",
        f"{CODE_STYLE}h{RESET}|{CODE_STYLE}help{RESET} [{CODE_STYLE}command{RESET}] print help or help for a command",
        f"{CODE_STYLE}enter{RESET} to repeat the previous command",
        sep="\n",
        end="\n\n",
    )


def run_debug(
    choice: DebugChoice,
    command: str,
    arguments: str,
    stdin_path: Path,
):
    if choice == DebugChoice.NONE:
        debug_choices = ",".join(
            {str(choice) for choice in DebugChoice if choice != DebugChoice.NONE}
        )

        print("To debug run with the debug flag")
        print(
            f"{CODE_STYLE}python3.11 {argv[0]} source_file --debug [{{{debug_choices}}}]{RESET}"
        )
        print()
        return

    print(f"{TEST_REPORT_STYLE}debug{RESET}: {choice}")
    print(choice.description)
    print()

    if choice != DebugChoice.RUN:
        gdb_help()

    stdin = f" < {stdin_path}" if stdin_path.exists() else ""
    run = f"-ex 'run {arguments} {stdin}'"

    match choice:
        case DebugChoice.BREAK:
            shell(f"gdb {command} -ex 'b main' {run}")
        case DebugChoice.BACKTRACE | DebugChoice.BT:
            shell(f"gdb {command} {run} -ex 'bt'")
        case DebugChoice.RUN:
            shell(f"./{command} {arguments}", stdin_path=stdin_path)


def remove_nested_commas(text: str):
    """
    Remove commas inside parentheses or braces.
    Assumes balanced and matching parentheses and braces.
    """
    depth = 0
    result = ""
    for character in text:
        match character:
            case "(" | "{":
                depth += 1
            case ")" | "}":
                depth -= 1
            case ",":
                if depth != 0:
                    continue
        result += character

    assert depth == 0, "Unbalanced parentheses or braces"
    return result


def find_any_unclosed_fstreams(source_file: Path) -> list[str] | None:
    source_code = read_file(source_file)

    # Remove comments in case the comments contain mention of fstream
    source_code_no_comments = re.sub(
        r"(//.*?$)|(/\*.*?\*/)",
        "",
        source_code,
        flags=re.DOTALL | re.MULTILINE,
    )

    # Does not preserve the code structure, but easy for checking expressions that may include extraneous whitespace
    source_code_no_whitespace = "".join(source_code_no_comments.split())

    if "#include<fstream>" not in source_code_no_whitespace:
        return None

    result = re.findall(
        r"\b(?:i|o)?fstream([\s(]+\w+.*?);",  # ifstream(fin); or ifstream fin;
        source_code_no_comments,
        flags=re.DOTALL | re.MULTILINE,
    )

    unclosed_fstreams = list[str]([])

    for matches in result:
        # Remove nested commas to break only on multiple declarations `fstream fin(1,2,3), fout; -> fstream fin(123), fout;`
        for expression in remove_nested_commas(matches).split(","):
            found = re.findall(r"(\w+).*", expression)  # Get the first identifier

            assert len(found) == 1
            fstream_name = found[0]
            assert isinstance(fstream_name, str)

            if f"{fstream_name}.close();" not in source_code_no_whitespace:
                unclosed_fstreams.append(fstream_name)

    return unclosed_fstreams


def print_test_file(component_name: LiteralString, path: Path):
    if not path.exists():
        return

    print(f"{TEST_INFO_STYLE}{component_name}{RESET}")
    print(f"{CODE_STYLE}cat {path}{RESET}")
    cat(path)
    print()


def print_test_summary(
    command: str,
    is_print: bool,
    hint_path: Path,
    user_stdin_path: Path,
    fin_path: Path,
):
    print(f"{TEST_INFO_STYLE}command{RESET}")
    stdin = f" <{user_stdin_path}" if user_stdin_path.exists() else ""
    print(f"{CODE_STYLE}{command}{stdin}{RESET}")
    print()

    print_test_file("hint", hint_path)

    if not user_stdin_path.exists() and not fin_path.exists():
        return

    if not is_print:
        print("To view the test input run with the print flag")
        print(f"{CODE_STYLE}python3.11 {argv[0]} source_file --print{RESET}")
        print()
    else:
        print_test_file("stdin", user_stdin_path)
        print_test_file("fin", fin_path)


def has_warnings(script_config: ScriptConfig):
    is_warnings = False

    if not script_config.is_skip_fstream_check:
        try:  # Lots of regex, may fail
            unclosed_fstreams = find_any_unclosed_fstreams(script_config.source_file)
            if unclosed_fstreams:
                print_warning(
                    "Some fstreams were not closed:",
                    f"Disable this check with the {CODE_STYLE}--skip-fstream-check{RESET} flag",
                    "",
                    *[
                        f"- {CODE_STYLE}{fstream}{RESET}"
                        for fstream in unclosed_fstreams
                    ],
                    end="\n\n",
                )
                is_warnings = True
        except:
            print_fatal(
                "fstream check failed",
                f"Disable this check with the {CODE_STYLE}--skip-fstream-check{RESET} flag",
                end="\n\n",
            )

    if not script_config.is_skip_warnings_check and not check_compiler_warning(
        script_config
    ):
        print_warning(
            "Compiler warnings detected",
            f"Disable this check with the {CODE_STYLE}--skip-warnings-check{RESET} flag",
            end="\n\n",
        )
        compile_program(script_config)
        is_warnings = True

    return is_warnings


def print_test_header(test_name: str, progress: tuple[int, int]):
    short_test_name = "-".join(test_name.split("-")[1:])  # 001-short-test-name

    numerator, denominator = progress
    progress_text = f"({numerator + 1}/{denominator})"

    print(
        f"{YELLOW}{progress_text:7}{RESET} {TEST_HEADER_STYLE}{short_test_name}{RESET}"
    )


def run_test(
    script_config: ScriptConfig,
    test_path: Path,
    progress: tuple[int, int],
):
    print_test_header(test_path.name, progress)

    arguments_path = test_path / "arguments.txt"
    stdin_path = test_path / "stdin.txt"
    fin_path = test_path / "fin.txt"
    hint_path = test_path / "hint.txt"

    solution_stdout_path = test_path / "stdout.txt"
    solution_stderr_path = test_path / "stderr.txt"
    solution_fout_path = test_path / "fout.txt"

    user_stdout_path = test_path / "stdout.tmp.txt"
    user_stderr_path = test_path / "stderr.tmp.txt"
    user_fout_path = test_path / "fout.tmp.txt"
    user_leak_report_path = test_path / "leak-summary.tmp.txt"

    solution_exit_status = int(read_file(test_path / "exit-status.txt"))

    program_arguments = read_file(arguments_path) if arguments_path.exists() else ""
    command_with_arguments = (
        f"./student/{script_config.lab_name}/{script_config.bin_filename} {program_arguments}"
        if program_arguments
        else f"./student/{script_config.lab_name}/{script_config.bin_filename}"
    )

    program_is_passed, user_exit_status = run_program(
        command=command_with_arguments,
        timeout_duration=script_config.timeout_duration,
        expected_exit_status=solution_exit_status,
        stdin_path=stdin_path,
        user_stdout_path=user_stdout_path,
        user_stderr_path=user_stderr_path,
    )
    stdout_is_passed = diff_output(
        component_name="stdout",
        solution_output_path=solution_stdout_path,
        user_output_path=user_stdout_path,
        is_verbose=script_config.is_verbose,
        split_stdout_on=script_config.split_stdout_on,
        is_show_whitespaces=script_config.is_show_whitespace,
        is_no_color=script_config.is_no_diff_color,
    )
    stderr_is_passed = diff_output(
        component_name="stderr",
        solution_output_path=solution_stderr_path,
        user_output_path=user_stderr_path,
        is_verbose=script_config.is_verbose,
        split_stdout_on=None,
        is_show_whitespaces=script_config.is_show_whitespace,
        is_no_color=script_config.is_no_diff_color,
    )
    fout_is_passed = diff_output(
        component_name="fout",
        solution_output_path=solution_fout_path,
        user_output_path=user_fout_path,
        is_verbose=script_config.is_verbose,
        split_stdout_on=None,
        is_show_whitespaces=script_config.is_show_whitespace,
        is_no_color=script_config.is_no_diff_color,
    )
    leak_check_is_passed = run_leak_check(
        command=command_with_arguments,
        solution_exit_status=solution_exit_status,
        user_exit_status=user_exit_status,
        stdin_path=stdin_path,
        user_leak_report_path=user_leak_report_path,
        is_leak_check=script_config.is_leak_check
        and not script_config.is_skip_leak_check,
        is_verbose=script_config.is_verbose,
    )

    is_passed = all(
        [
            program_is_passed,
            stdout_is_passed,
            stderr_is_passed,
            fout_is_passed,
            leak_check_is_passed,
        ]
    )
    is_exit = not is_passed and not script_config.is_run_all

    if is_exit or script_config.is_verbose:
        print_test_summary(
            command=command_with_arguments,
            is_print=script_config.is_print,
            hint_path=hint_path,
            user_stdin_path=stdin_path,
            fin_path=fin_path,
        )
    else:
        print()

    if is_exit:
        run_debug(
            choice=script_config.debug,
            command=script_config.bin_filename.name,
            arguments=program_arguments,
            stdin_path=stdin_path,
        )
        exit(ExitCodes.TEST_FAILED.value)

    return is_passed


def run_tests(script_config: ScriptConfig):
    tests = sorted([test for test in script_config.tests_dir.iterdir() if test.is_dir()])
    len_tests = len(tests)

    all_tests_passed = all(
        [
            run_test(
                script_config,
                test_path=test_path,
                progress=(test_number, len_tests),
            )
            for test_number, test_path in enumerate(tests)
        ]
    )

    if has_warnings(script_config):
        exit(ExitCodes.WARNINGS.value)

    if all_tests_passed:
        print(f"{ALL_TESTS_PASSED_STYLE}All tests passed{RESET}")
