from typing import Optional, Tuple
from PIL import Image
from vcb_riscv.generate_blueprint_images import (
    _get_blueprint_image_path,
    generate_blueprint_images,
)
from vcb_riscv.vcb_blueprints.vcb_blueprint import VCBBlueprint
import logging

logger = logging.getLogger(__name__)


def get_blueprint_size(blueprint: VCBBlueprint) -> Optional[Tuple[int, int]]:
    """Get the blueprint width and height in pixels."""
    image_path = _get_blueprint_image_path(blueprint, scale=1)

    logger.info("Opening image %s for size", image_path)

    with open(image_path) as f:
        image = Image.open(f)
        size = image.size

    return size


if __name__ == "__main__":
    blueprints = generate_blueprint_images()

    for blueprint in blueprints:
        size = get_blueprint_size(blueprint)
        logger.info("Blueprint %s size is %s", blueprint.codename, str(size))
