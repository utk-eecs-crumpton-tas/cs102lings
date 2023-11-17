parse_flag() {
    local number_arguments=$#
    local flags="$1"
    local flag="$2"
    local options=($3)
    local default_value="${4:-none}"

    if [[ "$flag" != '--'* ]]; then
        local argument3=$( (($number_arguments >= 3)) && echo "'$3'")
        local argument4=$( (($number_arguments >= 4)) && echo "'$4'")

        echo -e "${ERROR_STYLE}Invalid synatx for parse_flag${RESET}:" >&2
        echo >&2
        echo "  '$1' '$2' $argument3 $argument4" >&2
        echo >&2
        echo >&2
        echo -e "Usage boolean:" >&2
        echo "  parse_flag 'flags' '--flag'" >&2
        echo >&2
        echo -e "Usage any option:" >&2
        echo "  parse_flag 'flags' '--flag' '' 'default-value=none'" >&2
        echo >&2
        echo -e "Usage options list:" >&2
        echo "  parse_flag 'flags' '--flag' 'option1 option2 ...' 'default-value=none'" >&2
        echo >&2
        return 1
    fi

    local is_boolean=false
    if (($number_arguments == 2)); then
        is_boolean=true
    fi

    local has_flag=false
    if [[ "${flags[*]}" == *"$flag"* ]]; then
        has_flag=true
    fi

    if "$is_boolean"; then
        echo -n "$has_flag"
        return
    fi

    if ! "$has_flag"; then
        echo -n "$default_value"
        return
    fi

    local after_flag="${flags##*$flag }"
    local flag_value="${after_flag%% *}"

    if [[ "$flag_value" == '' ]]; then
        echo -e "${ERROR_STYLE}Error${RESET}: no value for flag '$flag'" >&2
        return 1
    fi

    # Accept any value if no options are specified
    if [[ "${options[*]}" == '' ]]; then
        echo -n "$flag_value"
        return
    fi

    for option in "${options[@]}"; do
        if [[ "$flag_value" == "$option" ]]; then
            echo -n "$flag_value"
            return
        fi
    done

    echo -e "${ERROR_STYLE}Error${RESET}: invalid value '$flag_value' for flag '$flag'" >&2
    echo -e "Valid options: ${options[*]}" >&2
    return 1
}

if [[ "$0" == *'parse-flag.bash' ]]; then
    FLAGS=("${@}")
    FILE=$(parse_flag "${FLAGS[*]}" '--file' '') || exit 1
    VALUE=$(parse_flag "${FLAGS[*]}" '--value' 'foo bar baz') || exit 1
    IS_TRUE=$(parse_flag "${FLAGS[*]}" '--bool') || exit 1

    echo "file: $FILE"
    echo "value: $VALUE"
    echo "is_true: $IS_TRUE"
fi
