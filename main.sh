#!/bin/bash

#TODO: Errors & Success mng
#TODO: Time in sec for d1 processing
#TODO: Fix graph for d1 processing
#TODO: d2 processing -> C

source scripts/d1_processing.sh
source scripts/d2_processing.sh
source scripts/l_processing.sh
source scripts/s_processing.sh
source scripts/t_processing.sh
source scripts/utils.sh

SCRIPT_DIR=$(pwd)

if [ -z "$SCRIPT_DIR" ]; then
    echo -e "${BOLD}${BG_LIGHT_RED}Error! SCRIPT_DIR is not set.${RESET}"
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

        d1_start_time=$(date +%s)
        filter_csv_for_d1 "$LOCAL_CSV_FILE"
        generate_graph_for_d1
        d1_end_time=$(date +%s)
        d1_duration=$((${d1_end_time} - ${d1_start_time}))
        echo -e "${ITALIC}Duration of d1 processing: ${RESET}${BOLD}${CYAN}${d1_duration} ${RESET}${ITALIC}seconds"
        valid_option=true
        ;;
    -d2 | -l | -s | -t)
        echo -e "\n${YELLOW}TODO: $*\n"
        valid_option=true
        ;;
    *)
        echo -e "${BOLD}${BG_LIGHT_RED}Error! Invalid option: $1${RESET}"
        show_help
        exit 1
        ;;
    esac
    shift
done

if [ "$valid_option" = false ]; then
    echo -e "${BOLD}${BG_LIGHT_RED}Error! At least one valid option is required.${RESET}"
    show_help
    exit 1
fi
