#!/bin/bash
#TODO:
# generate_graph_for_d2() {
#     local input_file="data/d2_temp_data.csv"
#     local output_dir="images"
#     local graph_path="${output_dir}/d2_histogram.png"

#     if [[ ! -f "$input_file" ]]; then
#         echo "${BOLD}${BG_LIGHT_RED}Error! Input file not found: $input_file${RESET}"
#         return 1
#     fi

#     gnuplot -e "

#     "

#     if [[ -f "$graph_path" && -s "$graph_path" ]]; then
#         echo -e "${LIGHT_GREEN}Success! ${RESET}Histogram generated: $graph_path${RESET}"
#     else
#         echo -e "${BOLD}${BG_LIGHT_RED}Error! Failed to generate histogram or file is empty.${RESET}"
#         return 1
#     fi
# }
