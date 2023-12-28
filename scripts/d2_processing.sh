#!/bin/bash

filter_csv_for_d2() {
    local input_file="$1"
    local output_file="temp/d2_temp_data.csv"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "CSV file not found: $input_file"
        exit 1
    fi

    awk -F ';' '
    NR > 1 {
        driver = $6;
        distance = $5;
        driverDistance[driver] += distance;
    }
    END {
        for (driver in driverDistance) {
            print driver ";" driverDistance[driver];
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

generate_graph_for_d2() {
    local input_file="temp/d2_temp_data.csv"
    local graph_path="temp/d2_temp_graph.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file"
        exit 1
    fi

    gnuplot -e "
        reset;
        set terminal png size 1000,1000;
        set output '$graph_path';
        set datafile separator ';';

        set tmargin 3;

        set style data histograms;
        set style histogram rowstacked; 
        set style fill solid 1.0;
        set boxwidth 0.7;

        set ylabel 'Option -d2 : Distance = f(Driver)';
        set y2label 'DISTANCE (Km)';
        set xlabel 'DRIVER NAMES' rotate by -180 offset 0,-2;

        set xtics right rotate by 90 offset 0,-1 font ',13';
        unset ytics; 
        set y2tics center rotate by 90 font ',13';

        set y2range [0:*];

        plot '$input_file' using 2:xticlabels(1) axes x1y2 notitle with boxes lc rgb '#79e7ae';

    "

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "The graph for treatment D2 has been generated successfully: $graph_path"
        command convert $graph_path -rotate 90 images/d2_graph.png >/dev/null
        command display images/d2_graph.png &
    else
        alert_danger "Failed to generate graph for treatment D2 or file is empty."
        exit 1
    fi
}
