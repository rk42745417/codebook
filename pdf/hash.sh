#!/bin/bash

mkdir -p `dirname "$2"`
cpp -dD -P -fpreprocessed "$1" \
  | tr -d '[:space:]' | md5sum | cut -c-6 | tee "$2"
