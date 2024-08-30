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


def is_printable_char(char: str):
    match ord(char):
        # TAB, LF, CR
        case 9 | 10 | 13:
            return True
        # Control characters
        case code if 0 <= code < 32:
            return False
        # DEL
        case 127:
            return False
        case _:
            return True


def sanitize_binary_output(path: Path):
    """Replace any binary characters in the file with the replacement character (�)."""

    with open(path, "rb") as input_file:
        data = input_file.read().decode("utf-8", errors="replace")
        sanitized_data = "".join(
            [char if is_printable_char(char) else "�" for char in data]
        )
    with open(path, "w") as output_file:
        output_file.write(sanitized_data)
