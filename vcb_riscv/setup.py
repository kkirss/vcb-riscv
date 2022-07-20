import dataclasses
import logging

from . import settings
from .folders import ensure_folder
from .vcbb.vcbb import get_vcbb_executable_path

logger = logging.getLogger(__name__)


@dataclasses.dataclass()
class EnvContext:
    vcbb_executable: str
    cwd: str


def setup_env() -> EnvContext:
    ensure_folder(settings.DATA_PATH)

    vcbb_executable = get_vcbb_executable_path()

    env_context = EnvContext(
        vcbb_executable=vcbb_executable,
        cwd=settings.BASE_PATH,
    )

    logger.debug("Using env context: %s", env_context)

    return env_context
