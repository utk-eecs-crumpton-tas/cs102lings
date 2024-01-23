from pathlib import Path


def read_file(path: Path) -> str:
    with open(path, "r", encoding="utf-8") as file:
        return file.read()


def write_file(path: Path, content: str):
    if not content:
        return

    with open(path, "w", encoding="utf-8") as file:
        file.write(content)
