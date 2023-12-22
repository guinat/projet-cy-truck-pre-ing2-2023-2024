#!/bin/bash

filter_csv_for_d1() {
    local input_file="$1"
    local output_file="data/d1_temp_data.csv"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "CSV file not found: $input_file"
        exit 1
    fi

    awk -F';' '
    NR > 1 {
        count[$6]++
    }
    END {
        for (name in count) {
            print name ";" count[name]
        }
    }' "$input_file" | sort -t';' -k2nr | head -10 >"$output_file"

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
        alert_danger "Input file not found: $input_file"
        return 1
    fi

    gnuplot -e "
    reset;
    set terminal png size 800,800;
    set output '$graph_path';

    set ylabel 'Option -d1 : Nb routes = f(Driver)';
    set datafile separator ';';

    set style data histograms;
    set style histogram rowstacked; 
    set style fill solid 1.0 border -1;
    set boxwidth 0.6;

    set xlabel 'DRIVER NAMES' offset 0,-2;
    set y2label 'NB ROUTES';

    set grid ytics;

    set xtics right rotate by 90 offset 0,-1;

    unset ytics; 

    set y2tics right rotate by 90;
    set y2range [0:*];

    plot '$input_file' using 2:xticlabels(1) axes x1y2 notitle with boxes lc rgb 'green';

"

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "Histogram generated: $graph_path"
    else
        alert_danger "Failed to generate histogram or file is empty."
        return 1
    fi
}
