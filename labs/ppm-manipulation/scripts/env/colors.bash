BLACK='\e[30m'
RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
BLUE='\e[34m'
MAGENTA='\e[35m'
CYAN='\e[36m'
WHITE='\e[37m'

BRIGHT_BLACK='\e[90m'
BRIGHT_RED='\e[91m'
BRIGHT_GREEN='\e[92m'
BRIGHT_YELLOW='\e[93m'
BRIGHT_BLUE='\e[94m'
BRIGHT_MAGENTA='\e[95m'
BRIGHT_CYAN='\e[96m'
BRIGHT_WHITE='\e[97m'

DARK_BLACK='\e[38;5;0m'
DARK_RED='\e[38;5;1m'
DARK_GREEN='\e[38;5;2m'
DARK_YELLOW='\e[38;5;3m'
DARK_BLUE='\e[38;5;4m'
DARK_MAGENTA='\e[38;5;5m'
DARK_CYAN='\e[38;5;6m'
DARK_WHITE='\e[38;5;7m'

LIGHT_BLACK='\e[38;5;8m'
LIGHT_RED='\e[38;5;9m'
LIGHT_GREEN='\e[38;5;10m'
LIGHT_YELLOW='\e[38;5;11m'
LIGHT_BLUE='\e[38;5;12m'
LIGHT_MAGENTA='\e[38;5;13m'
LIGHT_CYAN='\e[38;5;14m'
LIGHT_WHITE='\e[38;5;15m'

BOLD='\e[1m'
ITALIC='\e[3m'
RESET='\e[0m'

hex_to_ansi() {
    local hex_color="$1"
    local r="0x${hex_color:1:2}"
    local g="0x${hex_color:3:2}"
    local b="0x${hex_color:5:2}"
    printf "\e[38;2;%d;%d;%dm" $r $g $b
}

EMERALD_700=$(hex_to_ansi "#047857")
YELLOW_300=$(hex_to_ansi "#fde047")
ROSE_600=$(hex_to_ansi "#e11d48")
BLUE_500=$(hex_to_ansi "#3b82f6")
BLUE_600=$(hex_to_ansi "#2563eb")
BLUE_700=$(hex_to_ansi "#1d4ed8")
BLUE_800=$(hex_to_ansi "#1e40af")
PURPLE_400=$(hex_to_ansi "#c084fc")
VIOLET_600=$(hex_to_ansi "#7c3aed")
INDIGO_500=$(hex_to_ansi "#6366f1")
CYAN_500=$(hex_to_ansi "#22d3ee")
GREEN_400=$(hex_to_ansi "#68d391")
RED_400=$(hex_to_ansi "#fc8181")

SLATE_900=$(hex_to_ansi "#1f2937")

# printf "${RED}This is red text${RESET}\n"
# printf "${GREEN}This is green text${RESET}\n"
# printf "${YELLOW}This is yellow text${RESET}\n"
# printf "${BLUE}This is blue text${RESET}\n"
# printf "${MAGENTA}This is magenta text${RESET}\n"
# printf "${CYAN}This is cyan text${RESET}\n"
# printf "${WHITE}This is white text${RESET}\n"

# echo

# printf "${DARK_RED}This is dark red text${RESET}\n"
# printf "${DARK_GREEN}This is dark green text${RESET}\n"
# printf "${DARK_YELLOW}This is dark yellow text${RESET}\n"
# printf "${DARK_BLUE}This is dark blue text${RESET}\n"
# printf "${DARK_MAGENTA}This is dark magenta text${RESET}\n"
# printf "${DARK_CYAN}This is dark cyan text${RESET}\n"
# printf "${DARK_WHITE}This is dark white text${RESET}\n"

# echo

# printf "${BRIGHT_RED}This is bright red text${RESET}\n"
# printf "${BRIGHT_GREEN}This is bright green text${RESET}\n"
# printf "${BRIGHT_YELLOW}This is bright yellow text${RESET}\n"
# printf "${BRIGHT_BLUE}This is bright blue text${RESET}\n"
# printf "${BRIGHT_MAGENTA}This is bright magenta text${RESET}\n"
# printf "${BRIGHT_CYAN}This is bright cyan text${RESET}\n"
# printf "${BRIGHT_WHITE}This is bright white text${RESET}\n"

# echo

# printf "${LIGHT_RED}This is light red text${RESET}\n"
# printf "${LIGHT_GREEN}This is light green text${RESET}\n"
# printf "${LIGHT_YELLOW}This is light yellow text${RESET}\n"
# printf "${LIGHT_BLUE}This is light blue text${RESET}\n"
# printf "${LIGHT_MAGENTA}This is light magenta text${RESET}\n"
# printf "${LIGHT_CYAN}This is light cyan text${RESET}\n"
# printf "${LIGHT_WHITE}This is light white text${RESET}\n"

ERROR_STYLE="$RED"
WARNING_STYLE="$YELLOW"

CODE_STYLE="$MAGENTA"

TEST_HEADER_STYLE="$BOLD"
TEST_SUBHEADER_STYLE="$BLUE"
TEST_SUCCESS_STYLE="$GREEN"
TEST_FAILURE_STYLE="$RED"
TEST_REPORT_STYLE="$CYAN$BOLD"
TEST_INFO_STYLE="$CYAN"

ALL_TESTS_PASSED_STYLE="$GREEN$BOLD"

if [[ "$0" == *'colors.bash' ]]; then
    printf "${ERROR_STYLE}Error:${RESET} an error occured\n"
    printf "Code style: ${CODE_STYLE}exec zsh${RESET}\n"
    echo

    printf "${TEST_HEADER_STYLE}Test header style${RESET}\n"
    printf "  ${TEST_SUBHEADER_STYLE}subheader${RESET} ${TEST_SUCCESS_STYLE}passed${RESET}\n"
    printf "  ${TEST_SUBHEADER_STYLE}subheader${RESET} ${TEST_FAILURE_STYLE}failed${RESET}\n"
    printf "${TEST_INFO_STYLE}Test info style${RESET}\n"
    echo
    printf "${ALL_TESTS_PASSED_STYLE}All tests passed style${RESET}\n"
fi
