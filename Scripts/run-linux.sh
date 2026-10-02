#!/usr/bin/env bash
set -euo pipefail

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
engine_root="${1:-${UE_ROOT:-}}"
if [[ -z "$engine_root" ]]; then
  echo "Usage: Scripts/run-linux.sh /absolute/path/to/UnrealEngine" >&2
  echo "Or set UE_ROOT to the Unreal Engine install directory." >&2
  exit 2
fi

editor="$engine_root/Engine/Binaries/Linux/UnrealEditor"
if [[ ! -x "$editor" ]]; then
  echo "Unreal Editor not found or not executable: $editor" >&2
  exit 2
fi

"$project_dir/Scripts/build-linux.sh" "$engine_root"
exec "$editor" "$project_dir/TidesOfTheForsaken.uproject" -log
