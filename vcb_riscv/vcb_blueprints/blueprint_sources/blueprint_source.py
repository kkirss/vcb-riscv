import dataclasses
from abc import ABC
from typing import Iterable

from vcb_riscv.setup import EnvContext
from vcb_riscv.vcb_blueprints.vcb_blueprint import VCBBlueprint


@dataclasses.dataclass(frozen=True)
class VCBBlueprintSource(ABC):
    """
    Source for Virtual Circuit Board blueprints.
    """

    base_path: str
    output_base_path: str

    SOURCE_NAME: str = NotImplemented

    def get_blueprints(self, env_context: EnvContext) -> Iterable[VCBBlueprint]:
        raise NotImplementedError()
