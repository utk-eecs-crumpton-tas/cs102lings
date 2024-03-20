from io import TextIOWrapper
from pathlib import Path
from subprocess import run, PIPE, DEVNULL
from typing import IO, Any
from .files import write_file
from .config import BIN_FILENAME

CPP_VERSION = "c++11"


def shell(
    command: str,
    stdin_path: Path | None = None,
    stdout: Path | IO[Any] | int | None = None,
    stderr: Path | IO[Any] | int | None = None,
):
    stdin = (
        open(stdin_path, "r", encoding="utf-8")
        if stdin_path is not None and stdin_path.exists()
        else None
    )

    stdout_is_path = isinstance(stdout, Path)
    stderr_is_path = isinstance(stderr, Path)

    subprocess = run(
        command,
        stdin=stdin,
        stdout=PIPE if stdout_is_path else stdout,
        stderr=PIPE if stderr_is_path else stderr,
        shell=True,
        check=False,
        executable="bash",
    )

    if isinstance(stdin, TextIOWrapper):
        stdin.close()

    if stdout_is_path:
        write_file(
            stdout,
            subprocess.stdout.decode(encoding="ascii", errors="replace"),
        )

    if stderr_is_path:
        write_file(
            stderr,
            subprocess.stderr.decode(encoding="ascii", errors="replace"),
        )

    return subprocess.returncode


def clean():
    shell(f"rm -rf {BIN_FILENAME} tests/**/*.tmp.txt")


def cat(path: Path):
    if not path.exists():
        return
    return shell(f"cat {path}")


def compile_program(source_file: Path):
    arguments = f"-std={CPP_VERSION} -Wall -Wextra -g -O0"
    return shell(f"g++ {arguments} -o {BIN_FILENAME} {source_file}") == 0


def check_compiler_warning(source_file: Path):
    arguments = f"-std={CPP_VERSION} -Wall -Wextra -Werror -Wno-sign-compare"
    return (
        shell(
            f"g++ {arguments} -o {BIN_FILENAME} {source_file}",
            stdout=DEVNULL,
            stderr=DEVNULL,
        )
        == 0
    )


def diff(original: Path, modified: Path):
    return (
        shell(
            f"diff {original} {modified}",
            stdout=DEVNULL,
            stderr=DEVNULL,
        )
        == 0
    )


def diff_y(
    is_no_color: bool,
    original: Path,
    modified: Path,
):
    # Mac diff does not support --color
    color_arg = "" if is_no_color else "--color"
    shell(f"diff -y {color_arg} {original} {modified}")


def command_exists(command: str):
    return shell(f"command -v {command}", stdout=DEVNULL, stderr=DEVNULL) == 0


def valgrind(
    command: str,
    stdin_path: Path,
    leak_report_path: Path,
):
    valgrind_arguments = "--leak-check=full --error-exitcode=1"
    return (
        shell(
            f"valgrind {valgrind_arguments} -- {command}",
            stdin_path=stdin_path,
            stdout=DEVNULL,
            stderr=leak_report_path,
        )
        == 0
    )
