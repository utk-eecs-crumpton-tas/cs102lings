from pathlib import Path
from .formatting import print_warning, CODE_STYLE, RESET

FILE_CHARACTER_LIMIT = 1024 * 16
OUTPUT_LIMIT = 400


def read_file(path: Path) -> str:
    with open(path, "r", encoding="utf-8") as file:
        return file.read()


def handle_output_limit(path: Path, content: str):
    if len(content) < FILE_CHARACTER_LIMIT:
        return content

    print_warning(
        f"Output file exceeded limit of {CODE_STYLE}{FILE_CHARACTER_LIMIT}{RESET} characters. Setting output to {CODE_STYLE}{OUTPUT_LIMIT}{RESET} characters",
        f"{CODE_STYLE}{path}{RESET}",
        end="\n\n",
    )

    return content[:OUTPUT_LIMIT] + "..."


def write_file(path: Path, content: str):
    if not content:
        return

    with open(path, "w", encoding="utf-8") as file:
        file.write(handle_output_limit(path, content))
