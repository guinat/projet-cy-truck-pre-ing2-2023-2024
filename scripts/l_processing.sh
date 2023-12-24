#!/bin/bash

filter_csv_for_l() {
    local input_file="$1"
    local output_file="temp/l_temp_data.csv"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "CSV file not found: $input_file"
        exit 1
    fi

    awk -F ';' '
    NR > 1 {
        journeyID = $1;
        distance = $5;
        journeyDistance[journeyID] += distance;
    }
    END {
        for (journeyID in journeyDistance) {
            print journeyID ";" journeyDistance[journeyID];
        }
    }' "$input_file" |
        sort -t';' -k2,2nr |
        head -10 |
        sort -k1,1nr >"$output_file"

    if [[ -s "$output_file" ]]; then
        alert_success "Top 10 drivers list generated: $output_file"
    else
        alert_danger "Failed to generate top 10 drivers list."
        exit 1
    fi

}

generate_graph_for_l() {
    local input_file="temp/l_temp_data.csv"
    local graph_path="images/l_histogram.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file"
        exit 1
    fi

    gnuplot -e "
        reset;
        set terminal png size 800,800;
        set output '$graph_path';
        set datafile separator ';';
        set title 'Option -l : Distance = f(Route)';

        set style data histograms;
        set style histogram rowstacked; 
        set style fill solid 1.0;
        set boxwidth 0.7;

        set ylabel 'DISTANCE (Km)';
        set xlabel 'ROUTE ID';

        set xtics  font ',10';
        set ytics  font ',10';

        set yrange [0:*];

        plot '$input_file' using 2:xticlabels(1) notitle with boxes lc rgb '#79e7ae';

    "

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "Histogram generated: $graph_path"
    else
        alert_danger "Failed to generate histogram or file is empty."
        exit 1
    fi
}
