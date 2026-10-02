#!/usr/bin/env bash
set -euo pipefail

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
engine_root="${1:-${UE_ROOT:-}}"
if [[ -z "$engine_root" ]]; then
  echo "Usage: Scripts/build-linux.sh /absolute/path/to/UnrealEngine" >&2
  echo "Or set UE_ROOT to the Unreal Engine install directory." >&2
  exit 2
fi

build_script="$engine_root/Engine/Build/BatchFiles/Linux/Build.sh"
if [[ ! -f "$build_script" ]]; then
  echo "Unreal Build.sh not found: $build_script" >&2
  exit 2
fi

"$build_script" TidesOfTheForsakenEditor Linux Development \
  "$project_dir/TidesOfTheForsaken.uproject" -WaitMutex
