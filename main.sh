#!/bin/bash

source scripts/d1_processing.sh
source scripts/d2_processing.sh
source scripts/l_processing.sh
source scripts/s_processing.sh
source scripts/t_processing.sh
source scripts/utils.sh

SCRIPT_DIR=$(pwd)

if [ -z "$SCRIPT_DIR" ]; then
    echo "Error: SCRIPT_DIR is not set."
    exit 1
fi

if [[ " $* " == *" -h "* ]]; then
    show_help
    exit 0
fi

CSV_FILE="$1"
LOCAL_CSV_FILE="${SCRIPT_DIR}/data/$(basename "$CSV_FILE")"

for DIR in temp images data; do
    DIR_PATH="${SCRIPT_DIR}/${DIR}"
    if [ ! -d "$DIR_PATH" ]; then
        mkdir -p --mode=a+rw "$DIR_PATH"
    fi
done

rm -f "${SCRIPT_DIR}/temp/"*

if [ -f "$CSV_FILE" ]; then
    cp "$CSV_FILE" "$LOCAL_CSV_FILE"
else
    echo "Error: Data file '$CSV_FILE' does not exist."
    exit 1
fi

shift
valid_option=false
while [ "$#" -gt 0 ]; do
    case "$1" in
    -h)
        show_help
        valid_option=true
        ;;
    -d1)
        filter_csv_for_d1 "$LOCAL_CSV_FILE"
        generate_graph_for_d1
        valid_option=true
        ;;
    -d2 | -l | -s | -t)
        echo -e "\n${YELLOW}TODO: $*\n"
        valid_option=true
        ;;
    *)
        echo "Invalid option: $1"
        show_help
        exit 1
        ;;
    esac
    shift
done

if [ "$valid_option" = false ]; then
    echo "Error: At least one valid option is required."
    show_help
    exit 1
fi
