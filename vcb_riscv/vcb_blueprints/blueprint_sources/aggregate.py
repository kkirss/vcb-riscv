from itertools import chain
from typing import Iterable

from .file_source import DATA_FILES_BLUEPRINT_SOURCE, PUBLIC_BLUEPRINTS_BLUEPRINT_SOURCE
from vcb_riscv.vcb_blueprints.vcb_blueprint import VCBBlueprint
from vcb_riscv.setup import EnvContext

ALL_SOURCES = {
    DATA_FILES_BLUEPRINT_SOURCE,
    PUBLIC_BLUEPRINTS_BLUEPRINT_SOURCE,
}


def get_aggregated_blueprints(env_context: EnvContext) -> Iterable[VCBBlueprint]:
    return chain(*(source.get_blueprints(env_context) for source in ALL_SOURCES))
