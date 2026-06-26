#!/usr/bin/env bash
set -e

MODE="${1:-train}"   # 'train' (default) or 'eval'


# --- config ---
K=1
# Allow override: ./run_pipe.sh <n>   (runs <n> epochs)
# EPOCHS=3
DEFAULT_EPOCHS=3
EPOCHS="${1:-(DEFAULT_EPOCHS)}"

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DATA_HDF5_DIR="$ROOT_DIR/pasadena_train_hdf5"
DATASET="$DATA_HDF5_DIR/dataset${K}.h5"
TEMPLATE_DIR="$ROOT_DIR/pasadena_tiles_2048_32_finetuned-demo"
TILES_DIR="$ROOT_DIR/pasadena_tiles_2048_32_finetuned${K}"
TRAIN_DIR="$ROOT_DIR/pasadena_train${K}_weights"
OUT_DIR="$TILES_DIR/output_pred"      # << single source of truth

####################################################
echo "=== CLEAN & SETUP ==="

if [ "$MODE" = "train" ]; then
  # only nuke weights when we actually train
  rm -rf "$TILES_DIR" "$TRAIN_DIR"
  mkdir -p "$DATA_HDF5_DIR"
  echo "Copying template into $TILES_DIR..."
  cp -r "$TEMPLATE_DIR/" "$TILES_DIR/"
  rm -f "$DATASET"
else
  # eval-only: keep TRAIN_DIR, just reset tiles + outputs
  rm -rf "$TILES_DIR"
  echo "Eval-only mode: reusing weights in $TRAIN_DIR"
  mkdir -p "$DATA_HDF5_DIR"
  echo "Copying template into $TILES_DIR..."
  cp -r "$TEMPLATE_DIR/" "$TILES_DIR/"
fi


# # 🔧 NEW: ensure no stale detections survive from the template
# if [ -d "$TILES_DIR/output" ]; then
#   echo "Clearing stale JSONs in $TILES_DIR/output ..."
#   find "$TILES_DIR/output" -type f -name "*.json" -delete
# fi

# (optional) stamp a run id for debugging
RUN_STAMP="$(date -u +'%Y%m%dT%H%M%SZ')"
echo "$RUN_STAMP" > "$TILES_DIR/.run_stamp"


# Start with a fresh HDF5 dataset
rm -f "$DATASET"

if [ "$MODE" = "train" ]; then
  ####################################################
  echo "=== STEP 1: dataset_preprocess.py ==="
  cd ./pasadena_data_256_RGB_train_backup
  python dataset_preprocess.py --seed_m ${K} --threshold 55
  cd "$ROOT_DIR"

  ####################################################
  echo "=== STEP 2: scripts.prepare => ${DATASET} ==="
  python -m scripts.prepare \
    ./pasadena_data_256_RGB_train_backup \
    "$DATASET" \
    --bands RGB

  ####################################################
  echo "=== STEP 3: scripts.train-gpu (EPOCHS=${EPOCHS}) ==="
  python -m scripts.train-gpu \
    "$DATASET" \
    "$TRAIN_DIR" \
    --epochs "$EPOCHS"

  ####################################################
  echo "=== STEP 4: scripts.tune ==="
  python -m scripts.tune \
    "$DATASET" \
    "$TRAIN_DIR"


  ####################################################
  echo "=== STEP 5: scripts.test ==="
  python -m scripts.test \
    "$DATASET" \
    "$TRAIN_DIR"


  PRED_DIR="$TILES_DIR/output_pred"   # 🔧 NEW
  rm -rf "$PRED_DIR"; mkdir -p "$PRED_DIR"

fi
####################################################
echo "=== STEP 6: scripts.inference-gpu-2 ==="
python -m scripts.inference-gpu-2 \
  ./pasadena_tiles_2048_32/images \
  "$TILES_DIR/output_pred" \
  "$TRAIN_DIR" \
  --bands RGB \
  --gpu_id 0 \
  --num_gpus 1

####################################################
echo "=== STEP 7: merge + evaluation ==="

cd "$TILES_DIR"

# nuke old artifacts
rm -f merged_pasadena.json tree_matches.geojson evaluation_metrics.csv \
      distance_histogram.png recall_threshold_plot.png recall_threshold_data.csv

bash merge_GeoJSON.sh                   # the version in $TILES_DIR
python evaluation-NEW-2.py

# Back in $TILES_DIR when eval finishes
# Append to a global log in ROOT
LOG_CSV="$ROOT_DIR/metrics_log.csv"
STAMP=$(cat .run_stamp 2>/dev/null || echo "NA")
MODE_COL="$MODE"   # from earlier
EPOCH_COL="$EPOCHS"
K_COL="$K"

# tack run info onto the metrics row (skip header)
tail -n +2 evaluation_metrics.csv | while IFS=, read -r metric value; do
  echo "$STAMP,$MODE_COL,$EPOCH_COL,$K_COL,$metric,$value" >> "$LOG_CSV"
done


