import logging
from pathlib import Path

from environs import Env

from vcb_riscv.folders import ensure_folder

env = Env()
env.read_env()

# Versions
VERSION = "0.1.0"

VERBOSE = env.bool("VERBOSE", True)

BASE_PATH = str(Path(__file__).parent.parent)
DATA_PATH = env("DATA_PATH", str(Path(BASE_PATH) / "data"))
ensure_folder(DATA_PATH)


# vcbb (Virtual Circuit Board Blueprint)
# Using: https://github.com/chrjen/vcbb
VCBB_REPO_URL = env("VCBB_REPO_URL", "https://github.com/chrjen/vcbb")
VCBB_REPO_LOCAL_PATH = env("VCBB_REPO_LOCAL_PATH", str(Path(DATA_PATH) / "vcbb"))
VCBB_EXECUTABLE_NAMES = env("VCBB_EXECUTABLE_NAMES", "vcbb.exe,vcbb")
GO_EXECUTABLE = env("GO_EXECUTABLE", "go")

# VCB blueprint sources
# File
BLUEPRINT_FILES_PUBLIC_FOLDER = env(
    "BLUEPRINT_FILES_PUBLIC_FOLDER", str(Path(BASE_PATH) / "library" / "vcb_blueprints")
)
BLUEPRINT_IMAGES_PUBLIC_FOLDER = env(
    "BLUEPRINT_IMAGES_PUBLIC_FOLDER",
    str(Path(BLUEPRINT_FILES_PUBLIC_FOLDER) / "images"),
)

BLUEPRINT_FILES_DATA_FOLDER = env(
    "BLUEPRINT_FILES_DATA_FOLDER", str(Path(DATA_PATH) / "blueprint_files")
)
BLUEPRINT_IMAGES_DATA_FOLDER = env(
    "BLUEPRINT_IMAGES_DATA_FOLDER", str(Path(DATA_PATH) / "blueprint_images")
)

logging.basicConfig(level=logging.DEBUG if VERBOSE else logging.INFO)
