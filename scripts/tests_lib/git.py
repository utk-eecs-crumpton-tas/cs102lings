from subprocess import DEVNULL
from pathlib import Path
from .shell import shell


def is_git_repo():
    return (
        shell(
            "git rev-parse --is-inside-work-tree",
            stdout=DEVNULL,
            stderr=DEVNULL,
        )
        == 0
    )


def git_path_is_modified(path: Path | None = None):
    if not is_git_repo():
        return False

    path_arg = f"{path} " if path is not None else ""

    return (
        shell(
            f'[[ "$(git status {path_arg} --porcelain)"  ]]',
            stdout=DEVNULL,
            stderr=DEVNULL,
        )
        == 0
    )
