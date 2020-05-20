#!/bin/bash
INPUT_FILE="../fix_messages_5_0.json"
OUTPUT_FILE="../src/fix_db.h"

if [ ! -f "${INPUT_FILE}" ]
then
    echo "Can't open ${INPUT_FILE}"
    exit
fi

echo "" > "${OUTPUT_FILE}"

echo "#pragma once" >> "${OUTPUT_FILE}"

