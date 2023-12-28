#!/bin/bash

source scripts/c_program.sh

t_processing() {

    local _DIR=$(pwd)
    local exec="_exec"
    local exec_path="progc/bin/$exec"
    local input_file="$1"
    local output_file="$_DIR/temp/t_temp_data.csv"

    command -v make >/dev/null 2>&1 || {
        alert_danger "Make is required but not installed. Aborting."
        exit 1
    }

    if [ ! -f "$exec_path" ]; then
        compile_c_program
    fi

    if [ -d "progc/bin" ]; then
        if (cd progc/bin && "./$exec" -t "$input_file" "$output_file" 2>&1); then
            if [[ -s "$output_file" ]]; then
                alert_success "Top 10 city list generated: $output_file"
            else
                alert_danger "Failed to generate top 10 city list."
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

generate_graph_for_t() {
    local input_file="temp/t_temp_data.csv"
    local graph_path="images/t_graph.png"

    if [[ ! -f "$input_file" ]]; then
        alert_danger "Input file not found: $input_file"
        exit 1
    fi

    gnuplot -e "
        reset;
        set terminal png size 1000,1000;
        set output '$graph_path';
        set datafile separator ';';
        set title 'Option -t : Nb routes = f(Towns)';

        set tmargin 3;

        set style data histograms;
        set style histogram clustered gap 1;
        set boxwidth 0.5;
        set style fill solid;

        set ylabel 'NB ROUTES';
        set xlabel 'TOWN NAMES';

        set xtics rotate by -45 font ',13';
        set ytics font ',13';

        set yrange [0:*] noreverse;

        set key at screen 0.9, screen 0.9;

        set offset 0.2,0.2;

        plot '${input_file}' using 2:xtic(1) title 'Total routes' with boxes lt rgb '#79e7ae', \
        '' using 3 title 'First town' with boxes lt rgb '#5dca93';
    "

    if [[ -f "$graph_path" && -s "$graph_path" ]]; then
        alert_success "The graph for treatment T has been generated successfully: $graph_path"
        command display images/t_graph.png &
    else
        alert_danger "Failed to generate graph for treatment T or file is empty."
        exit 1
    fi
}
