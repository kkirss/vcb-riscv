#!/bin/bash

# Update a VCB project JSON file from a config file
# Usage: update_vcb_project_value.sh <vcb_file> <config_file>
# Example: update_vcb_project_value.sh project.vcb vcb_config.json

# Config file is a JSON object to merge into the .vcb project
# Optionally, the key can be an alias, as defined in config_aliases.json
# Note: config_aliases.json can set the alias to an array of nested keys/indexes

VCB_FILE="$1"
VCB_CONFIG_FILE="$2"

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
CONFIG_ALIASES_FILE="${SCRIPT_DIR}/config_aliases.json"

# Need to write to a temporary file because jq doesn't support in-place editing
VCB_TEMP_FILE="$VCB_FILE.tmp"

JQ_BIND_NORMALIZED_CONFIG='($config | to_entries | map({value, path: ($config_aliases[.key] // .key)}) | map(.path |= if type == "array" then . else [.] end)) as $normalized_config'
JQ_SET_VALUES='reduce $normalized_config[] as $item (.; setpath($item.path; $item.value))'

jq --tab "$JQ_BIND_NORMALIZED_CONFIG | $JQ_SET_VALUES" "$VCB_FILE" --argfile config "$VCB_CONFIG_FILE" --argfile config_aliases "$CONFIG_ALIASES_FILE" > "$VCB_TEMP_FILE" && mv -f "$VCB_TEMP_FILE" "$VCB_FILE"

# Remove temporary file even if jq errored
if [ -f "$VCB_TEMP_FILE" ]; then
    rm "$VCB_TEMP_FILE"
fi
