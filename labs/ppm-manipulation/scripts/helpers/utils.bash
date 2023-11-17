read_and_substitute_input() {
    local input_path="$1"
    local output_path="$2"
    local fin_path="$3"
    local fout_path="$4"

    if ! [[ -f "$input_path" ]]; then
        return
    fi

    sed -e "s|<fin>|$fin_path|g" -e "s|<fout>|$fout_path|g" "$input_path" >"$output_path"

    cat "$output_path"
}
