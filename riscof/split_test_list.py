import logging
import sys
import yaml
from pathlib import Path

logger = logging.getLogger(__name__)


def split_test_list(test_list_path: Path, test_output_folder: Path) -> None:
    """Split the test list into separate files."""
    test_output_folder.mkdir(parents=True, exist_ok=True)

    with open(test_list_path) as f:
        test_list: dict[str, dict] = yaml.full_load(f)

    for test_key, test_content in test_list.items():
        test_assembly_name = test_key.rsplit('/', 1)[-1]
        test_name = test_assembly_name.rsplit('-', 1)[0]
        test_output_path = test_output_folder / f'{test_name}.yaml'

        with open(test_output_path, 'w') as f:
            yaml.dump({test_key: test_content}, f)

            logger.info('Split test %s to separate file %s', test_name, test_output_path)


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])

    split_test_list(input_path, output_path)
