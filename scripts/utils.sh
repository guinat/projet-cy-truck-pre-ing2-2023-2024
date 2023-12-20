source scripts/colors.sh

delimiter="-------------------------------------------"
print_delimiter() {
    printf "\n%s\n" "${delimiter}"
}

show_help() {
    print_delimiter
    printf "${BOLD}${CYAN}Usage:${RESET}$0 [path_to_csv_file] [option]${RESET}\n"
    printf "${BOLD}${LIGHT_GREEN}Options:${RESET}\n"
    printf "  ${BOLD}${YELLOW}-h${RESET}      Display this help message\n"
    printf "  ${BOLD}${YELLOW}-d1${RESET}     Process D1\n"
    printf "  ${BOLD}${YELLOW}-d2${RESET}     Process D2\n"
    printf "  ${BOLD}${YELLOW}-l${RESET}      Process L\n"
    printf "  ${BOLD}${YELLOW}-s${RESET}      Process S\n"
    printf "  ${BOLD}${YELLOW}-t${RESET}      Process T\n"
    print_delimiter
}

#TODO: Errors & Success mng
