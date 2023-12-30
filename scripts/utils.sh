# Include the color definitions from colors.sh
source scripts/colors.sh

# Function to print a delimiter line
print_delimiter() {
    echo "--------------------------------"
}

# Function to display help message
show_help() {
    print_delimiter
    echo -e "${BOLD}${CYAN}Usage:${RESET}   $0 [path_to_csv_file] [option]${RESET}"
    echo -e "${BOLD}${LIGHT_GREEN}Options:${RESET}"
    echo -e "  ${BOLD}${YELLOW}-h${RESET}      Display this help message"
    echo -e "  ${BOLD}${YELLOW}-d1${RESET}     Process D1"
    echo -e "  ${BOLD}${YELLOW}-d2${RESET}     Process D2"
    echo -e "  ${BOLD}${YELLOW}-l${RESET}      Process L"
    echo -e "  ${BOLD}${YELLOW}-s${RESET}      Process S"
    echo -e "  ${BOLD}${YELLOW}-t${RESET}      Process T"
    print_delimiter
}

# Function to display a success message
alert_success() {
    local alert_msg="$1"
    echo -e "${BOLD}${GREEN}Success:${RESET} ${alert_msg}"
}

# Function to display an error message
alert_danger() {
    local alert_msg="$1"
    echo -e "${BOLD}${RED}Error:${RESET}   ${RED}${alert_msg}${RESET}"
}

# Function to display a warning message
alert_warning() {
    local alert_msg="$1"
    echo -e "${BOLD}${YELLOW}Warning:${RESET} ${alert_msg}"
}

# Function to display an info message
alert_info() {
    local alert_msg="$1"
    echo -e "${BOLD}${CYAN}Info:${RESET}    ${alert_msg}"
}
