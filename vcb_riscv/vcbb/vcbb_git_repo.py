import os.path
import logging

import git

from vcb_riscv import settings

logger = logging.getLogger(__name__)


def clone_vcbb_git_repo():
    if not os.path.isdir(settings.VCBB_REPO_LOCAL_PATH):
        logger.debug(
            "Cloning vcbb git repo to %s",
            settings.VCBB_REPO_LOCAL_PATH,
        )
        git.Repo.clone_from(settings.VCBB_REPO_URL, settings.VCBB_REPO_LOCAL_PATH)
