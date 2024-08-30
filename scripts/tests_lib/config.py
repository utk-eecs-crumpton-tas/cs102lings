from argparse import ArgumentParser, Namespace
from dataclasses import dataclass
from enum import Enum
from json import loads
from pathlib import Path
from typing import Any, Literal, TypeVar, overload
from .files import read_file

LABS_DIR = Path("labs")

T = TypeVar("T")


def validate(value: Any, expected_type: type[T], message: str | None = None) -> T:
    assert isinstance(value, expected_type), message
    return value


class ExitCodes(Enum):
    SCRIPT_ERROR = 1
    WARNINGS = 2
    BUILD_FAILED = 3
    TEST_FAILED = 4
    TIMEOUT = 124


class DebugChoice(Enum):
    BREAK = "break"
    BACKTRACE = "backtrace"
    BT = "bt"
    RUN = "run"
    NONE = "none"

    def __str__(self):
        return self.value

    @property
    def description(self):
        match self:
            case DebugChoice.BREAK:
                return "Pausing execution at the start of the program"
            case DebugChoice.BACKTRACE | DebugChoice.BT:
                return "Running the program through and printing a backtrace on failure"
            case DebugChoice.RUN:
                return "Running the program normally without GDB"
            case DebugChoice.NONE:
                return "No debugging"


@dataclass(init=False)
class ScriptConfig:
    source_file: str
    lab_name: str
    scripts_dir: str
    tests_dir: str
    is_clean: bool
    is_verbose: bool
    is_show_whitespace: bool
    is_no_diff_color: bool
    is_skip_leak_check: bool
    is_skip_fstream_check: bool
    is_skip_warnings_check: bool
    is_run_all: bool
    is_print: bool
    timeout_duration: str
    debug: DebugChoice

    is_leak_check: bool
    split_stdout_on: str

    def __init__(self, cli_arguments: Namespace):
        self.lab_name = validate(cli_arguments.lab_name, str)
        self.is_clean = validate(cli_arguments.clean, bool)
        self.is_verbose = validate(cli_arguments.verbose, bool)
        self.is_show_whitespace = validate(cli_arguments.show_whitespace, bool)
        self.is_no_diff_color = validate(cli_arguments.no_diff_color, bool)
        self.is_skip_leak_check = validate(cli_arguments.skip_leak_check, bool)
        self.is_skip_fstream_check = validate(cli_arguments.skip_fstream_check, bool)
        self.is_skip_warnings_check = validate(cli_arguments.skip_warnings_check, bool)
        self.is_run_all = validate(cli_arguments.run_all, bool)
        self.is_print = validate(cli_arguments.print, bool)
        self.timeout_duration = validate(cli_arguments.timeout, str)
        self.debug = validate(cli_arguments.debug, DebugChoice)

        CONFIG_PATH = LABS_DIR / self.lab_name / "testconfig.json"
        SCRIPTS_DIR = Path("scripts")
        TESTS_DIR = LABS_DIR / self.lab_name / Path("tests")
        BIN_FILENAME = Path("lab.bin")
        self.scripts_dir = SCRIPTS_DIR
        self.bin_filename = BIN_FILENAME
        self.tests_dir = TESTS_DIR
        self.source_file = Path("student") / self.lab_name / Path("{filename}.cpp".format(filename = self.lab_name))

        content = read_file(CONFIG_PATH)
        config = loads(content)

        self.is_leak_check = validate(
            config["leak_check"],
            bool,
            "`config.leak_check` was not a boolean",
        )
        self.split_stdout_on = validate(
            config["split_stdout_on"],
            str,
            "`config.split_stdout_on` was not a string",
        )


@overload
def parse_script_config(is_print_help: Literal[True]) -> None: ...


@overload
def parse_script_config(is_print_help: Literal[False] = False) -> ScriptConfig: ...


def parse_script_config(is_print_help=False):
    parser = ArgumentParser()
    parser.add_argument(
        "lab_name",
        type=str,
        help="The source file to test",
    )
    parser.add_argument(
        "--clean",
        action="store_true",
        help="Clean up temporary files",
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="Display test summary for passed tests",
    )
    parser.add_argument(
        "-w",
        "--show-whitespace",
        action="store_true",
        help="Replace spaces with visible characters",
    )
    parser.add_argument(
        "--no-diff-color",
        action="store_true",
        help="Disable colored diff output",
    )
    parser.add_argument(
        "--skip-leak-check",
        action="store_true",
        help="Disable valgrind leak check",
    )
    parser.add_argument(
        "--skip-fstream-check",
        action="store_true",
        help="Disable checking if fstreams closed",
    )
    parser.add_argument(
        "--skip-warnings-check",
        action="store_true",
        help="Disable checking if program has warnings",
    )
    parser.add_argument(
        "-r",
        "--run-all",
        action="store_true",
        help="Continue running tests after a failure",
    )
    parser.add_argument(
        "-p",
        "--print",
        action="store_true",
        help="Print the test input",
    )
    parser.add_argument(
        "-t",
        "--timeout",
        type=str,
        default="3s",
        help="Timeout for each test. Default: 10s",
    )
    parser.add_argument(
        "-d",
        "--debug",
        type=DebugChoice,
        choices=set(DebugChoice),
        nargs="?",
        const=DebugChoice.BREAK,
        default=DebugChoice.NONE,
        help="Attach a gdb instance on failure",
    )

    if is_print_help:
        parser.print_help()
        return

    return ScriptConfig(parser.parse_args())
