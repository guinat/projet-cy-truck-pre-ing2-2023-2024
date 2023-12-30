#!/bin/bash

# Include the custom colors file for display
source scripts/colors.sh

# Define the function to compile the C program
compile_c_program() {
    local prog_dir="progc" # Directory of the C program to compile

    # Display an informational message to the user
    alert_info "Compiling C program..."

    # Try to change to the program directory
    if ! cd "$prog_dir"; then
        alert_danger "Failed to enter directory '$prog_dir'. Aborting."
        return 1 # Return an error code
    fi

    # Compile using 'make' and redirect output to /dev/null to suppress compilation messages
    if ! make >/dev/null 2>&1; then
        alert_danger "Compilation failed. Aborting."
        return 1 # Return an error code
    fi

    # Return to the previous directory
    cd - >/dev/null

    # Display a success message
    alert_success "Compilation successful."
}
