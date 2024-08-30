#!/bin/bash
#
if [ -z "$1" ]; then
  printf "No lab name given."
  exit 1;
fi

python3.11 ./scripts/test.py $1
