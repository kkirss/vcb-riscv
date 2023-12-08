RISCV_PREFIX ?= /opt/riscv

MKFILE_PATH := $(lastword $(abspath $(MAKEFILE_LIST)))
DIR := $(realpath $(dir $(MKFILE_PATH)))

RISCOF_CONFIG := $(DIR)/config.ini
RISCOF_PLUGINS_REPO_DIR := $(DIR)/riscv-plugins
RISCV_ARCH_TEST_REPO_DIR := $(DIR)/riscv-arch-test

RISCOF_WORK_DIR := $(DIR)/riscof_work
RISCOF_TEST_LIST := $(RISCOF_WORK_DIR)/test_list.yaml
RISCOF_SEPARATE_TEST_FOLDER := $(RISCOF_WORK_DIR)/separate_tests

RISCOF_FLAGS := --config="$(RISCOF_CONFIG)" --suite="$(RISCV_ARCH_TEST_REPO_DIR)/riscv-test-suite/" --env="$(RISCV_ARCH_TEST_REPO_DIR)/riscv-test-suite/env" --work-dir="$(RISCOF_WORK_DIR)"

####
# Setup riscof
####
$(RISCOF_PLUGINS_REPO_DIR):
	@echo "Cloning riscv-plugins..."
	@git clone https://gitlab.com/incoresemi/riscof-plugins.git "$(RISCOF_PLUGINS_REPO_DIR)"

$(RISCV_ARCH_TEST_REPO_DIR):
	@which riscof > /dev/null || (echo "riscof is not installed" && echo "Please run programs/setup/ubuntu-riscof.sh to install on Ubuntu" && exit 1)
	@[ -f "$(SPIKE_PATH)" ] || (echo "Spike RISC-V simulator is not installed" && echo "Please run programs/setup/ubuntu-riscof.sh to install on Ubuntu" && exit 1)
	@which riscv32-unknown-elf-gcc > /dev/null 2>&1 || (echo "Assuming riscv64-unknown-elf-gcc to be multilib compiler" && echo "Linking riscv32-unknown-elf-gcc to riscv64-unknown-elf-gcc" && ln -sTf "$(RISCV_PREFIX)/bin/riscv64-unknown-elf-gcc" "$(RISCV_PREFIX)/bin/riscv32-unknown-elf-gcc")
	@echo "Cloning riscv-arch-test..."
	@riscof arch-test --clone --dir="$(RISCV_ARCH_TEST_REPO_DIR)"

####
# Generate riscof test list
####

$(RISCOF_TEST_LIST): $(RISCV_ARCH_TEST_REPO_DIR)
	@echo "Generating riscof test list and database..."
	@riscof testlist $(RISCOF_FLAGS)

.PHONY: riscof_test_list
riscof_test_list: $(RISCOF_TEST_LIST) ## Generate riscof test list

####
# Generate riscof separate tests
####

$(RISCOF_SEPARATE_TEST_FOLDER): $(RISCOF_TEST_LIST)
	@echo "Generating riscof separate test folder..."
	@python3 $(DIR)/split_test_list.py "$(RISCOF_TEST_LIST)" "$(RISCOF_SEPARATE_TEST_FOLDER)"

.PHONY: riscof_separate_tests
riscof_separate_tests: $(RISCOF_SEPARATE_TEST_FOLDER) ## Generate riscof separate tests

$(RISCOF_SEPARATE_TEST_FOLDER)/%.yaml: $(RISCOF_SEPARATE_TEST_FOLDER)

####
# Clean riscof build folders
####

RISCOF_DUT_FOLDERS = $(wildcard $(RISCOF_WORK_DIR)/**/**/src/**/dut)
RISCOF_REF_FOLDERS = $(wildcard $(RISCOF_WORK_DIR)/**/**/src/**/ref)

clean_riscof_build_folders:
	@echo "Cleaning up riscof build folders..."
	rm -rf $(RISCOF_DUT_FOLDERS) $(RISCOF_REF_FOLDERS)

clean_riscof_build_folder_%:
	@echo "Cleaning up riscof build folder for $*..."
	rm -rf $(RISCOF_WORK_DIR)/**/**/src/$**/dut
	rm -rf $(RISCOF_WORK_DIR)/**/**/src/$**/ref

####
# VCB VMEM conversion
####

RISCOF_DUT_ELF_FILES = $(wildcard $(RISCOF_WORK_DIR)/**/**/src/**/dut/my.elf)
RISCOF_DUT_ELF_D_FILES = $(patsubst %.elf,%.elf.d,$(RISCOF_DUT_ELF_FILES))

.PHONY: riscof_disassemble
riscof_disassemble: $(RISCOF_DUT_ELF_D_FILES) ## Disassemble riscof tests

RISCOF_VCB_VMEM_FILES = $(patsubst %.elf,%.vcbmem,$(RISCOF_DUT_ELF_FILES))

.PHONY: riscof_vcb_vmem
riscof_vcb_vmem: $(RISCOF_VCB_VMEM_FILES) ## Convert riscof tests to VCB VMEM files (.vcbmem)

####
# Disassemble riscof tests
####

RISCOF_DUT_ELF_D_FILES = $(patsubst %.elf,%.elf.d,$(RISCOF_DUT_ELF_FILES))

.PHONY: riscof_disassemble
riscof_disassemble: $(RISCOF_DUT_ELF_D_FILES) ## Disassemble riscof tests

####
# Build/Run riscof tests
####

SPIKE_PATH := /opt/riscv/riscv64-unknown-elf/bin/spike

define riscof_run =
	@echo "Running riscof tests from $<..."
	riscof --verbose debug run $(RISCOF_FLAGS) --testfile="$(1)" $(2)
endef

.PHONY: riscof_run
riscof_run: $(RISCOF_TEST_LIST) $(RISCOF_PLUGINS_REPO_DIR) clean_riscof_build_folders ## Run all riscof tests
	$(call riscof_run,$<,--no-browser)

.PHONY: riscof_run_%
riscof_run_%: $(RISCOF_SEPARATE_TEST_FOLDER)/%.yaml $(RISCOF_TEST_LIST) $(RISCOF_PLUGINS_REPO_DIR) clean_riscof_build_folder_% ## Run riscof test x
	$(call riscof_run,$<,--no-browser)
