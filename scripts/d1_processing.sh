#!/bin/bash

filter_csv_for_d1() {
    local input_file="$1"
    local output_file="data/d1_temp_data.csv"

    if [[ ! -f "$input_file" ]]; then
        echo -e "${BOLD}${BG_LIGHT_RED}Error! CSV file not found: $input_file${RESET}"
        return 1
    fi

    awk -F';' 'NR > 1 {count[$6] ++$2} END {for (name in count) print count[name] ";" name}' "$input_file" | sort -nr | head -10 >"$output_file"

    if [[ -s "$output_file" ]]; then
        alert_success "Top 10 drivers list generated: $output_file"
    else
        alert_danger "Failed to generate top 10 drivers list."
        return 1
    fi
}

generate_graph_for_d1() {
    local input_file="data/d1_temp_data.csv"
    local output_dir="images"
    local graph_path="${output_dir}/d1_histogram.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file$"
        return 1
    fi

    gnuplot -e "
        set terminal png size 800,600;
        set output '$graph_path';

        set title 'Top 10 Drivers by Number of Trips';
        set datafile separator ';';

        set style data histograms;
        set style histogram rowstacked;
        set style fill solid 1.0 border -1;
        set boxwidth 0.45;

        set xlabel 'Drivers';
        set ylabel 'Count';

        set yrange [0:*];
        set auto x;

        set xtics font ',10';

        plot '$input_file' using 1:xticlabels(2) with boxes title 'Trips';
    "

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "Histogram generated: $graph_path"
    else
        alert_danger "Failed to generate histogram or file is empty."
        return 1
    fi
}
