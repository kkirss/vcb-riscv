import dataclasses
from typing import Optional


@dataclasses.dataclass()
class VCBBlueprint:
    name: str
    blueprint_code: str

    output_base_path: str

    file_path: Optional[str] = None

    @property
    def codename(self):
        return self.name.replace(" ", "-").lower()
