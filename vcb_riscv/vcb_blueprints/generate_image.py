import logging
import subprocess
from subprocess import CalledProcessError

from vcb_riscv.setup import EnvContext
from vcb_riscv.vcb_blueprints.vcb_blueprint import VCBBlueprint

logger = logging.getLogger(__name__)


def generate_blueprint_image(
    blueprint: VCBBlueprint,
    *,
    output_file: str,
    env_context: EnvContext,
    scale: int = 1,
) -> None:
    """
    Generate an image from a vcb blueprint, based on its base64 code.
    """
    vcbb_executable = env_context.vcbb_executable

    if blueprint.file_path:
        args = [
            vcbb_executable,
            "decode",
            "--output",
            f"{output_file}",
            "--scale",
            f"{int(scale)}",
            f"{blueprint.file_path}",
        ]
    else:
        args = [
            "echo",
            f"{blueprint.blueprint_code}",
            "|",
            vcbb_executable,
            "decode",
            "--output",
            f"{output_file}",
            "--scale",
            f"{int(scale)}",
        ]
        logger.error("Decoding blueprints from text only does not work currently.")

    logger.info("Running (in %s) %s", env_context.cwd, " ".join(args))
    process = subprocess.run(" ".join(args), cwd=env_context.cwd)

    try:
        process.check_returncode()
    except CalledProcessError as e:
        raise ValueError("vcbb failed") from e
