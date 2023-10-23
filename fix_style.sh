#!/bin/bash

set -e
set -o pipefail

if [ -z "$1" ]; then
  echo -e "\nPlease call '$0 <path/to/source/code>' to run this command!\n"
  exit 1
fi

dir=$1
if [ "${dir: -1}" != "/" ]; then
  dir+="/"
fi

echo "Fixing cpp style in $dir..."
clang-format -style=file -i \
  $(find $dir \
  -type d \
  \( -name third_party \) -prune -false \
  -o \
  \( \( -name "*.h" -o -name "*.cpp" \) \) -print)
echo "Done"

