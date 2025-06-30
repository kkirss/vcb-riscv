#!/usr/bin/env bash
make -e TEST_NAME=lui riscof_run
make -e TEST_NAME=auipc riscof_run
make -e TEST_NAME=add riscof_run
make -e TEST_NAME=sll riscof_run
make -e TEST_NAME=jal riscof_run
make -e TEST_NAME=jalr riscof_run
make -e TEST_NAME=blt riscof_run
make -e TEST_NAME=bgeu riscof_run
make -e TEST_NAME=lb-align riscof_run
make -e TEST_NAME=sb-align riscof_run
