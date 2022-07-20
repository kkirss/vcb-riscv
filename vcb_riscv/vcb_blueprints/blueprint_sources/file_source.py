import dataclasses
from pathlib import Path
from typing import Iterable

from vcb_riscv.vcb_blueprints.vcb_blueprint import VCBBlueprint
from vcb_riscv import settings

from .blueprint_source import VCBBlueprintSource
from vcb_riscv.setup import EnvContext
from vcb_riscv.folders import ensure_folder


VCB_BLUEPRINT_FILE_EXTENSION = ".vcb"


@dataclasses.dataclass(frozen=True)
class FileVCBBlueprintSource(VCBBlueprintSource):
    """
    Source loading blueprints from files.
    """

    SOURCE_NAME = "file"

    recursive: bool = False

    def _get_blueprint_paths(self, from_path: Path) -> Iterable[Path]:
        for blueprint_path in Path(from_path).iterdir():
            if self.recursive:
                if blueprint_path.is_dir():
                    yield from self._get_blueprint_paths(blueprint_path)

                    continue

            if blueprint_path.suffix == VCB_BLUEPRINT_FILE_EXTENSION:
                yield blueprint_path

    def get_blueprints(self, env_context: EnvContext) -> Iterable[VCBBlueprint]:
        ensure_folder(self.base_path)

        for blueprint_path in self._get_blueprint_paths(Path(self.base_path)):
            with open(blueprint_path) as f:
                blueprint_code = f.read()

            blueprint = VCBBlueprint(
                name=blueprint_path.stem,
                blueprint_code=blueprint_code,
                output_base_path=self.output_base_path,
                file_path=str(blueprint_path),
            )
            yield blueprint


DATA_FILES_BLUEPRINT_SOURCE = FileVCBBlueprintSource(
    base_path=settings.BLUEPRINT_FILES_DATA_FOLDER,
    output_base_path=settings.BLUEPRINT_IMAGES_DATA_FOLDER,
)

PUBLIC_BLUEPRINTS_BLUEPRINT_SOURCE = FileVCBBlueprintSource(
    base_path=settings.BLUEPRINT_FILES_PUBLIC_FOLDER,
    output_base_path=settings.BLUEPRINT_IMAGES_PUBLIC_FOLDER,
    recursive=True,
)
