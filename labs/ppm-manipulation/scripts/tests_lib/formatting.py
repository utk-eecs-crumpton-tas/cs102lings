from sys import stderr


INDENT = "  "

# BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
# WHITE = "\033[37m"

BOLD = "\033[1m"
ITALIC = "\033[3m"
RESET = "\033[0m"

CODE_STYLE = MAGENTA
WARNING_STYLE = YELLOW
ERROR_STYLE = RED
FATAL_STYLE = f"{RED}{BOLD}"

TEST_HEADER_STYLE = BOLD
TEST_SUCCESS_STYLE = GREEN
TEST_SUBHEADER_STYLE = BLUE
TEST_FAILURE_STYLE = RED
TEST_REPORT_STYLE = f"{CYAN}{BOLD}"
TEST_INFO_STYLE = CYAN

ALL_TESTS_PASSED_STYLE = f"{GREEN}{BOLD}"


def print_message(
    header: str = "",
    message: tuple[str, ...] = (),
    end="\n",
    indent=0,
):
    indentation = " " * indent

    print(
        indentation,
        end="",
        file=stderr,
    )

    if header:
        print(
            header,
            end=" ",
            file=stderr,
        )

    print(
        *message,
        sep=f"\n{indentation}",
        end=end,
        file=stderr,
    )


def print_warning(
    *message: str,
    end="\n",
    indent=0,
):
    print_message(
        header=f"{WARNING_STYLE}Warning{RESET}:",
        message=message,
        end=end,
        indent=indent,
    )


def print_error(
    *message: str,
    end="\n",
    indent=0,
):
    print_message(
        header=f"{ERROR_STYLE}Error{RESET}:",
        message=message,
        end=end,
        indent=indent,
    )


def print_fatal(
    *message: str,
    end="\n",
    indent=0,
):
    print_message(
        header=f"{FATAL_STYLE}Fatal gradescript error{RESET}:",
        message=message,
        end=end,
        indent=indent,
    )


def print_test_failure(test_name: str, reason: str):
    print(
        f"{INDENT}{TEST_SUBHEADER_STYLE}{test_name:10}{RESET} {TEST_FAILURE_STYLE}{reason}{RESET}"
    )


def print_result(test_name: str, is_passed: bool):
    if is_passed:
        print(
            f"{INDENT}{TEST_SUBHEADER_STYLE}{test_name:10}{RESET} {TEST_SUCCESS_STYLE}passed{RESET}"
        )
    else:
        print_test_failure(test_name, "failed")


def print_missing(test_name: str):
    print_test_failure(test_name, "missing")


def print_skipped(test_name: str):
    print(
        f"{INDENT}{TEST_SUBHEADER_STYLE}{test_name:10}{RESET} {TEST_FAILURE_STYLE}skipped{RESET}"
    )
