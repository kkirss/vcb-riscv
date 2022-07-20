import pathlib


def ensure_folder(folder_path: str):
    pathlib.Path(folder_path).mkdir(parents=True, exist_ok=True)
