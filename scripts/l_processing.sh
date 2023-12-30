#!/bin/bash

# Function to filter CSV data for treatment L
filter_csv_for_l() {
    local input_file="$1"
    local output_file="temp/l_temp_data.csv"

    # Check if the input CSV file exists
    if [[ ! -f "$input_file" ]]; then
        alert_danger "CSV file not found: $input_file"
        exit 1
    fi

    # Use AWK to process the CSV data
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

    # Check if the output file is not empty
    if [[ -s "$output_file" ]]; then
        alert_success "Top 10 drivers list generated: $output_file"
    else
        alert_danger "Failed to generate top 10 drivers list."
        exit 1
    fi
}

# Function to generate a graph for treatment L
generate_graph_for_l() {
    local input_file="temp/l_temp_data.csv"
    local graph_path="images/l_graph.png"

    # Check if the input data file exists
    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file"
        exit 1
    fi

    # Use Gnuplot to create a graph from the data
    gnuplot -e "
        reset;
        set terminal png size 1000,1000;
        set output '$graph_path';
        set datafile separator ';';
        set title 'Option -l : Distance = f(Route)';

        set style data histograms;
        set style histogram rowstacked; 
        set style fill solid 1.0;
        set boxwidth 0.7;

        set ylabel 'DISTANCE (Km)';
        set xlabel 'ROUTE ID';

        set xtics  font ',13';
        set ytics  font ',13';

        set yrange [0:*];

        plot '$input_file' using 2:xticlabels(1) notitle with boxes lc rgb '#79e7ae';

    "

    # Check if the graph file was successfully generated and not empty
    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "The graph for treatment L has been generated successfully: $graph_path"
        command display images/l_graph.png &
    else
        alert_danger "Failed to generate graph for treatment L or file is empty."
        exit 1
    fi
}
