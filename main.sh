#!/bin/bash
source scripts/c_program.sh

source scripts/d1_processing.sh
source scripts/d2_processing.sh
source scripts/l_processing.sh
source scripts/s_processing.sh
source scripts/t_processing.sh
source scripts/t_processing.sh

source scripts/utils.sh

if ! command -v gnuplot >/dev/null; then
    alert_danger "GnuPlot is not installed. Please install it to generate charts."
    exit 1
fi

SCRIPT_DIR=$(pwd)

if [ -z "$SCRIPT_DIR" ]; then
    alert_danger "SCRIPT_DIR is not set."
    exit 1
fi

if [[ " $* " == *" -h "* ]]; then
    show_help
    exit 0
fi

if [ "$#" -lt 1 ]; then
    alert_danger "No input file provided. Please specify a CSV file."
    show_help
    exit 1
fi

CSV_FILE="$1"
CSV_FILENAME=$(basename "$CSV_FILE")

if [ ! -f "$CSV_FILE" ]; then
    alert_danger "CSV file not found at $CSV_FILE"
    exit 1
fi

for DIR in temp images data demo; do
    DIR_PATH="${SCRIPT_DIR}/${DIR}"
    if [ ! -d "$DIR_PATH" ]; then
        mkdir -p --mode=a+rw "$DIR_PATH"
    fi
done

rm -f "${SCRIPT_DIR}/temp/"*

cp "$CSV_FILE" "${SCRIPT_DIR}/data/${CSV_FILENAME}"

shift

valid_option=false
while [ "$#" -gt 0 ]; do
    case "$1" in
    -h)
        show_help
        valid_option=true
        ;;
    -d1)
        d1_start_time=$(date +%s)
        filter_csv_for_d1 "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_d1
        d1_end_time=$(date +%s)
        d1_duration=$((${d1_end_time} - ${d1_start_time}))
        alert_info "Duration of d1 processing: ${d1_duration} seconds"
        valid_option=true
        ;;
    -d2)
        d2_start_time=$(date +%s)
        filter_csv_for_d2 "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_d2
        d2_end_time=$(date +%s)
        d2_duration=$((${d2_end_time} - ${d2_start_time}))
        alert_info "Duration of d2 processing: ${d2_duration} seconds"
        valid_option=true
        ;;
    -l)
        l_start_time=$(date +%s)
        filter_csv_for_l "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_l
        l_end_time=$(date +%s)
        l_duration=$((${l_end_time} - ${l_start_time}))
        alert_info "Duration of l processing: ${l_duration} seconds"
        valid_option=true
        ;;
    -t)
        t_start_time=$(date +%s)
        t_processing "${SCRIPT_DIR}/data/${CSV_FILENAME}"
        generate_graph_for_t
        t_end_time=$(date +%s)
        t_duration=$((${t_end_time} - ${t_start_time}))
        alert_info "Duration of t processing: ${t_duration} seconds"
        valid_option=true
        ;;
    -s)
        echo -e "\n${YELLOW}TODO: $1\n"
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

if [ "$valid_option" = false ]; then
    alert_warning "No processing option provided. Only CSV file was copied."
    show_help
    exit 0
fi
