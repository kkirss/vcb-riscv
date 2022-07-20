import logging
import subprocess
from pathlib import Path
from typing import Optional

from vcb_riscv import settings
from . import constants
from .vcbb_git_repo import clone_vcbb_git_repo

logger = logging.getLogger(__name__)


def _look_for_executable_files(warn_if_not_exists: bool = True) -> Optional[str]:
    all_files_in_repo = list(Path(settings.VCBB_REPO_LOCAL_PATH).iterdir())

    executable_path: Optional[str] = None

    for potential_executable_name in constants.VCBB_EXECUTABLE_NAMES:
        for file_in_repo in all_files_in_repo:
            if potential_executable_name == file_in_repo.name:
                executable_path = str(file_in_repo)
                break

    if not executable_path and warn_if_not_exists:
        logger.warning(
            "Did not find a vcbb executable (%s) in repo path (%s) from %s",
            ",".join(constants.VCBB_EXECUTABLE_NAMES),
            settings.VCBB_REPO_LOCAL_PATH,
            " ".join(map(str, all_files_in_repo)),
        )
        return None

    return executable_path


def build_vcbb() -> Optional[str]:
    """
    Build vcbb (Virtual Circuit Board Blueprint).

    Using: https://github.com/chrjen/vcbb .

    :return: path to executable to run vcbb or None if not found.
    """
    if not Path(settings.VCBB_REPO_LOCAL_PATH).exists():
        clone_vcbb_git_repo()

    executable_path: Optional[str] = _look_for_executable_files(
        warn_if_not_exists=False
    )

    if not executable_path:
        args = [
            settings.GO_EXECUTABLE,
            "build",
        ]

        logger.info("(%s) %s", settings.VCBB_REPO_LOCAL_PATH, " ".join(args))
        subprocess.run(
            # executable=settings.GO_EXECUTABLE,
            args=args,
            cwd=settings.VCBB_REPO_LOCAL_PATH,
        )

    executable_path = _look_for_executable_files(warn_if_not_exists=True)

    return executable_path
