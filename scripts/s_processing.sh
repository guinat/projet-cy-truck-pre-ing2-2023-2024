#!/bin/bash

source scripts/c_program.sh

s_processing() {

    local _DIR=$(pwd)
    local exec="_exec"
    local exec_path="progc/bin/$exec"
    local input_file="$1"
    local output_file="$_DIR/temp/s_temp_data.csv"

    command -v make >/dev/null 2>&1 || {
        alert_danger "Make is required but not installed. Aborting."
        exit 1
    }

    if [ ! -f "$exec_path" ]; then
        compile_c_program
    fi

    if [ -d "progc/bin" ]; then
        if (cd progc/bin && "./$exec" -s "$input_file" "$output_file" 2>&1); then
            if [[ -s "$output_file" ]]; then
                alert_success "Top 50 routes list generated: $output_file"
            else
                alert_danger "Failed to generate top 50 routes list."
                exit 1
            fi
        else
            echo "Failed at: $(pwd)"
            alert_danger "Failed to change directory to 'progc' or to execute the program."
            exit 1
        fi
    else
        alert_danger "Directory 'progc' not found."
        exit 1
    fi
}

generate_graph_for_s() {
    local input_file="temp/s_temp_data.csv"
    local graph_path="images/s_graph.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file"
        exit 1
    fi

    gnuplot -e "
    reset;
    set terminal png size 1600,1000;
    set output '$graph_path';
    set datafile separator ';';
    set title 'Option -s : Distance = f(Route)';
    set xlabel 'ROUTE ID' offset 0,-3;
    set ylabel 'DISTANCE (Km)';

    set xtics center rotate by 45 font ',13' offset 0,-2;
    set ytics font ',13';
    set yrange [0:*];
    set key at screen 0.9, screen 0.9;

    plot '$input_file' using 0:3:5 with filledcurves lt rgb '#79e7ae' title 'Distance Max/Min (Km)', \
         '' using 4:xticlabels(2) with line lw 2 title 'Distance Average (Km)'
"

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "The graph for treatment S has been generated successfully: $graph_path"
        command display images/s_graph.png &
    else
        alert_danger "Failed to generate graph for treatment S or file is empty."
        exit 1
    fi
}
