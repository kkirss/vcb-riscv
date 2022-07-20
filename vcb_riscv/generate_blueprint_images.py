import logging
from pathlib import Path
from typing import Optional

from vcb_riscv.folders import ensure_folder
from vcb_riscv.vcb_blueprints.generate_image import generate_blueprint_image
from vcb_riscv.vcb_blueprints.vcb_blueprint import VCBBlueprint
from .vcb_blueprints.blueprint_sources.aggregate import get_aggregated_blueprints
from .setup import setup_env, EnvContext

logger = logging.getLogger(__name__)


DEFAULT_SCALES = [1, 4, 8]


def _get_blueprint_image_path(blueprint: VCBBlueprint, scale: int) -> str:
    ensure_folder(blueprint.output_base_path)

    scale = int(scale)

    if scale == 1:
        filename = f"{blueprint.codename}.png"
    else:
        filename = f"{blueprint.codename}_{scale}x.png"

    return str(Path(blueprint.output_base_path) / filename)


def generate_blueprint_images(scales: Optional[list[int]] = None) -> list[VCBBlueprint]:
    """
    Generate images for all blueprints.

    :returns: List of image paths for the generated blueprint images.
    """

    if scales is None:
        scales = DEFAULT_SCALES
    logger.info("Setting up env...")

    env_context: EnvContext = setup_env()

    logger.info("Generating blueprint images...")

    blueprints = list(get_aggregated_blueprints(env_context))

    for blueprint in blueprints:
        for scale in scales:
            try:
                generate_blueprint_image(
                    blueprint=blueprint,
                    output_file=_get_blueprint_image_path(blueprint, scale),
                    env_context=env_context,
                    scale=scale,
                )
            except ValueError:
                logger.exception(
                    "Blueprint image generation failed for blueprint %s at scale %s",
                    blueprint,
                    scale,
                )

    return blueprints


if __name__ == "__main__":
    generate_blueprint_images()
