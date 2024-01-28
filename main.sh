#!/bin/bash

# Include the C program functions from c_program.sh
source scripts/c_program.sh

# Include processing scripts for different options
source scripts/d1_processing.sh
source scripts/d2_processing.sh
source scripts/l_processing.sh
source scripts/t_processing.sh
source scripts/s_processing.sh

# Include utility functions
source scripts/utils.sh

# Check if GnuPlot is installed
if ! command -v gnuplot >/dev/null 2>&1; then
    alert_danger "GnuPlot is not installed. Please install it."
    alert_info "sudo apt install gnuplot"
    exit 1
fi

# Check if ImageMagick is installed
if ! command -v convert >/dev/null 2>&1; then
    alert_danger "ImageMagick is not installed. Please install it."
    alert_info "sudo apt install imagemagick"
    exit 1
fi

SCRIPT_DIR=$(pwd)

# Check if SCRIPT_DIR is set
if [ -z "$SCRIPT_DIR" ]; then
    alert_danger "SCRIPT_DIR is not set."
    exit 1
fi

# Display help message if -h option is used
if [[ " $* " == *" -h "* ]]; then
    show_help
    exit 0
fi

# Check if at least one argument is provided (path to CSV file)
if [ "$#" -lt 1 ]; then
    alert_danger "No input file provided. Please specify a CSV file."
    show_help
    exit 1
fi

CSV_FILE="$1"
CSV_FILENAME=$(basename "$CSV_FILE")

# Check if the CSV file exists
if [ ! -f "$CSV_FILE" ]; then
    alert_danger "CSV file not found at $CSV_FILE"
    show_help
    exit 1
fi

# Create necessary directories (temp, images, data)
for DIR in temp images data; do
    DIR_PATH="${SCRIPT_DIR}/${DIR}"
    if [ ! -d "$DIR_PATH" ]; then
        mkdir -p --mode=a+rw "$DIR_PATH"
    fi
done

# Remove any existing files in the 'temp' directory
rm -f "${SCRIPT_DIR}/temp/"*

# Copy the CSV file to the 'data' directory
cp "$CSV_FILE" "${SCRIPT_DIR}/data/${CSV_FILENAME}"

# Process command line options
shift

verify_csv_format
cd progc/verify
./_exec "${SCRIPT_DIR}/data/${CSV_FILENAME}"

# Check if verify file format terminated successfully
if [ $? -eq 0 ]; then
    alert_success "File format is correct."
else
    alert_danger "An error has occurred, check the log file"
    exit 1
fi

cd ../..

valid_option=false
while [ "$#" -gt 0 ]; do
    case "$1" in
    -h)
        show_help
        valid_option=true
        ;;
    -d1)
        # Measure the start time for d1 processing
        d1_start_time=$(date +%s%N)
        filter_csv_for_d1 "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_d1
        # Measure the end time for d1 processing
        d1_end_time=$(date +%s%N)
        # Calculate the duration of d1 processing in seconds
        d1_duration=$(echo "scale=3; ($d1_end_time - $d1_start_time) / 1000000000" | bc)
        alert_info "Duration of d1 processing: ${d1_duration} seconds"
        valid_option=true
        ;;
    -d2)
        # Measure the start time for d2 processing
        d2_start_time=$(date +%s%N)
        filter_csv_for_d2 "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_d2
        # Measure the end time for d2 processing
        d2_end_time=$(date +%s%N)
        # Calculate the duration of d2 processing in seconds
        d2_duration=$(echo "scale=3; ($d2_end_time - $d2_start_time) / 1000000000" | bc)
        alert_info "Duration of d2 processing: ${d2_duration} seconds"
        valid_option=true
        ;;
    -l)
        # Measure the start time for l processing
        l_start_time=$(date +%s%N)
        filter_csv_for_l "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_l
        # Measure the end time for l processing
        l_end_time=$(date +%s%N)
        # Calculate the duration of l processing in seconds
        l_duration=$(echo "scale=3; ($l_end_time - $l_start_time) / 1000000000" | bc)
        alert_info "Duration of l processing: ${l_duration} seconds"
        valid_option=true
        ;;
    -t)
        # Measure the start time for t processing
        t_start_time=$(date +%s%N)
        # cut -d ';' -f 1-4 "${SCRIPT_DIR}/data/${CSV_FILENAME}" >"${SCRIPT_DIR}/data/filtered.csv"
        t_processing
        generate_graph_for_t
        # Measure the end time for t processing
        t_end_time=$(date +%s%N)
        # Calculate the duration of t processing in seconds
        t_duration=$(echo "scale=3; ($t_end_time - $t_start_time) / 1000000000" | bc)
        alert_info "Duration of t processing: ${t_duration} seconds"
        valid_option=true
        ;;
    -s)
        # Measure the start time for s processing
        s_start_time=$(date +%s%N)
        s_processing "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_s
        # Measure the end time for s processing
        s_end_time=$(date +%s%N)
        # Calculate the duration of s processing in seconds
        s_duration=$(echo "scale=3; ($s_end_time - $s_start_time) / 1000000000" | bc)
        alert_info "Duration of s processing: ${s_duration} seconds"
        valid_option=true
        ;;
    *)
        alert_danger "Invalid option: $1"
        show_help
        exit 1
        ;;
    esac
    shift
done

# Display a warning if no processing option was provided (only CSV file was copied)
if [ "$valid_option" = false ]; then
    alert_warning "No processing option provided. Only CSV file was copied."
    show_help
    exit 0
fi
