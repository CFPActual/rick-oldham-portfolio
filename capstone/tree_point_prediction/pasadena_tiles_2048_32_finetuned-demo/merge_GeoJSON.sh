#!/usr/bin/env bash
set -euo pipefail
OUT=merged_pasadena.json
SRC_DIR=${SRC_DIR:-output_pred}   # default; can override via env

rm -f "$OUT"
ogrmerge.py -single -overwrite_ds -o "$OUT" -f GeoJSON -nln merged_pasadena "$SRC_DIR"/*.json
echo "Merged $(ls -1 "$SRC_DIR"/*.json | wc -l) tiles into $OUT"
