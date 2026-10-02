#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
for source in Tests/*Tests.cpp; do
  name="${source##*/}"
  binary="/tmp/tides-${name%.cpp}"
  g++ -std=c++17 -Wall -Wextra -Werror -I Source/TidesOfTheForsaken/Public "$source" -o "$binary"
  "$binary"
done
