# Set variables
set(RISCV_PREFIX "/opt/riscv")
set(SPIKE_PATH "${RISCV_PREFIX}/riscv64-unknown-elf/bin/spike")

set(RISCOF_CONFIG "${CMAKE_CURRENT_LIST_DIR}/config.ini")
set(RISCOF_PLUGINS_REPO_DIR "${CMAKE_CURRENT_LIST_DIR}/riscv-plugins")
set(RISCV_ARCH_TEST_REPO_DIR "${CMAKE_CURRENT_LIST_DIR}/riscv-arch-test")
set(RISCOF_WORK_DIR "${CMAKE_CURRENT_LIST_DIR}/riscof_work")

set(RISCOF_TEST_LIST "${RISCOF_WORK_DIR}/test_list.yaml")
set(RISCOF_SEPARATE_TEST_FOLDER "${RISCOF_WORK_DIR}/separate_tests")

set(RISCOF_FLAGS
    --config=${RISCOF_CONFIG}
    --suite=${RISCV_ARCH_TEST_REPO_DIR}/riscv-test-suite/
    --env=${RISCV_ARCH_TEST_REPO_DIR}/riscv-test-suite/env
    --work-dir=${RISCOF_WORK_DIR}
)

add_custom_command(
    COMMENT "Cloning riscv-plugins"
    OUTPUT ${RISCOF_PLUGINS_REPO_DIR}
    COMMAND git clone "https://gitlab.com/incoresemi/riscof-plugins.git" "${RISCOF_PLUGINS_REPO_DIR}"
)

add_custom_command(
    COMMENT "Cloning riscv-arch-test"
    OUTPUT ${RISCV_ARCH_TEST_REPO_DIR}
    COMMAND which riscof > /dev/null || (echo "riscof is not installed" && echo "Please run setup/ubuntu-riscof.sh to install on Ubuntu" && exit 1)
    COMMAND [ -f "${SPIKE_PATH}" ] || (echo "Spike RISC-V simulator is not installed" && echo "Please run setup/ubuntu-riscof.sh to install on Ubuntu" && exit 1)
    COMMAND which riscv32-unknown-elf-gcc > /dev/null 2>&1 || (echo "Assuming riscv64-unknown-elf-gcc to be multilib compiler" && echo "Linking riscv32-unknown-elf-gcc to riscv64-unknown-elf-gcc" && ln -sTf "${RISCV_PREFIX}/bin/riscv64-unknown-elf-gcc" "${RISCV_PREFIX}/bin/riscv32-unknown-elf-gcc")
    COMMAND riscof arch-test --clone --dir="${RISCV_ARCH_TEST_REPO_DIR}"
)

add_custom_command(
    COMMENT "Generating riscof test list and database"
    DEPENDS ${RISCOF_PLUGINS_REPO_DIR} ${RISCV_ARCH_TEST_REPO_DIR}
    OUTPUT ${RISCOF_TEST_LIST}
    COMMAND riscof testlist ${RISCOF_FLAGS}
)

add_custom_command(
    COMMENT "Generating riscof separate tests"
    DEPENDS ${RISCOF_TEST_LIST}
    OUTPUT ${RISCOF_SEPARATE_TEST_FOLDER}
    COMMAND python3 ${CMAKE_CURRENT_LIST_DIR}/split_test_list.py ${RISCOF_TEST_LIST} ${RISCOF_SEPARATE_TEST_FOLDER}
)

# Target for generating riscof separate tests
add_custom_target(riscof_separate_tests
    DEPENDS ${RISCOF_SEPARATE_TEST_FOLDER}
)

# Target to run all riscof tests
add_custom_target(riscof_run_all
    COMMENT "Running all riscof tests"
    DEPENDS ${RISCOF_TEST_LIST}
    COMMAND rm -rf ${RISCOF_WORK_DIR}/**/**/src/**/dut
    COMMAND rm -rf ${RISCOF_WORK_DIR}/**/**/src/**/ref
    COMMAND riscof --verbose debug run ${RISCOF_FLAGS} --testfile=${RISCOF_TEST_LIST} --no-browser
)

# Target to run a specific riscof test
# Must set env var TEST_NAME to the name of the test
add_custom_target(riscof_run
    COMMENT "Running riscof test $ENV{TEST_NAME}"
    DEPENDS ${RISCOF_SEPARATE_TEST_FOLDER}
    COMMAND rm -rf ${RISCOF_WORK_DIR}/**/**/src/$ENV{TEST_NAME}*/dut
    COMMAND rm -rf ${RISCOF_WORK_DIR}/**/**/src/$ENV{TEST_NAME}*/ref
    COMMAND riscof --verbose debug run ${RISCOF_FLAGS} --testfile=${RISCOF_SEPARATE_TEST_FOLDER}/$ENV{TEST_NAME}.yaml --no-browser
)
