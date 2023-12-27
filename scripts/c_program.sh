#!/bin/bash

source scripts/colors.sh

compile_c_program() {
    local prog_dir="progc"

    alert_info "Compiling C program..."

    if ! cd "$prog_dir"; then
        alert_danger "Failed to enter directory '$prog_dir'. Aborting."
        return 1
    fi

    if ! make >/dev/null 2>&1; then
        alert_danger "Compilation failed. Aborting."
        return 1
    fi

    cd - >/dev/null

    alert_success "Compilation successful."
}
