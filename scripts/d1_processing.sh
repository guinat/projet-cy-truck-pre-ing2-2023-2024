#!/bin/bash

filter_csv_for_d1() {
    local input_file="$1"
    local output_file="temp/d1_temp_data.csv"
    local graph_file="images/d1_histogram.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "CSV file not found: $input_file"
        exit 1
    fi

    awk -F ';' '
    NR > 1 {
        key = $6 "|" $1;  
        if (!(key in driverRoute)) {
            driverRoute[key] = 1;
            driverCount[$6]++;
        }
    }
    END {
        for (driver in driverCount) {
            print driver ";" driverCount[driver];
        }
    }' "$input_file" |
        sort -t';' -k2,2nr -k1,1 |
        head -10 >"$output_file"

    if [[ -s "$output_file" ]]; then
        alert_success "Top 10 drivers list generated: $output_file"
    else
        alert_danger "Failed to generate top 10 drivers list."
        exit 1
    fi

}

generate_graph_for_d1() {
    local input_file="temp/d1_temp_data.csv"
    local graph_path="images/d1_histogram.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file"
        exit 1
    fi

    gnuplot -e "
        reset;
        set terminal png size 800,800;
        set output '$graph_path';
        set datafile separator ';';

        set style data histograms;
        set style histogram rowstacked; 
        set style fill solid 1.0;
        set boxwidth 0.7;

        set ylabel 'Option -d1 : Nb routes = f(Driver)';
        set y2label 'NB ROUTES';
        set xlabel 'DRIVER NAMES' rotate by -180 offset 0,-2;

        set xtics right rotate by 90 offset 0,-1;
        unset ytics; 
        set y2tics center rotate by 90;

        set y2range [0:*];

        plot '$input_file' using 2:xticlabels(1) axes x1y2 notitle with boxes lc rgb '#79e7ae';

    "

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "Histogram generated: $graph_path"
    else
        alert_danger "Failed to generate histogram or file is empty."
        exit 1
    fi
}
