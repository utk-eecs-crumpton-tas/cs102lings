from tests_lib.config import parse_script_config
from tests_lib.shell import clean
from tests_lib.testing import ExitCodes, compile_program, run_tests
from tests_lib.formatting import (
    CODE_STYLE,
    RESET,
    print_error,
    print_warning,
)
from tests_lib.git import git_path_is_modified


def main():

    script_config = parse_script_config()
    TESTS_DIR = script_config.tests_dir
    SCRIPTS_DIR = script_config.scripts_dir
    
    if not TESTS_DIR.is_dir() or not SCRIPTS_DIR.is_dir():
        parse_script_config(True)
        print()
        print_error(
            f"{CODE_STYLE}Test{RESET} and {CODE_STYLE}scripts{RESET} directories not found",
            "Run this script from the root of the lab directory",
            f"Example: {CODE_STYLE}python3.11 {SCRIPTS_DIR}/test.py source_file{RESET}",
        )
        exit(ExitCodes.SCRIPT_ERROR.value)

    clean(script_config)
    if script_config.is_clean:
        return

    if git_path_is_modified(TESTS_DIR):
        print_warning(
            "Some of the test files have been modified",
            f"You can fix this run running {CODE_STYLE}git restore {TESTS_DIR}{RESET} in your current directory",
            end="\n\n",
        )

    if git_path_is_modified(SCRIPTS_DIR):
        print_warning(
            "Some of the script files have been modified",
            f"You can fix this run running {CODE_STYLE}git restore {SCRIPTS_DIR}{RESET} in your current directory",
            end="\n\n",
        )

    if not script_config.source_file.is_file():
        print_error(
            f"source_file: {CODE_STYLE}{script_config.source_file}{RESET} does not exist",
            f"Example: {CODE_STYLE}python3.11 {SCRIPTS_DIR}/test.py source_file{RESET}",
        )
        exit(ExitCodes.SCRIPT_ERROR.value)

    if not compile_program(script_config):
        print_error("Build failed")
        exit(ExitCodes.BUILD_FAILED.value)

    run_tests(script_config)


if __name__ == "__main__":
    main()
