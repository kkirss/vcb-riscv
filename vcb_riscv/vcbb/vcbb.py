import shutil

from . import constants
from .vcbb_build import build_vcbb


def get_vcbb_executable_path() -> str:
    for executable_name in constants.VCBB_EXECUTABLE_NAMES:
        if shutil.which(executable_name):
            return executable_name

    executable_path = build_vcbb()

    if executable_path:
        return executable_path

    raise EnvironmentError("Could not find vcbb executable")
