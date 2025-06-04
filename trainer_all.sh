#!/bin/bash

echo "Starting batch training from /data/untrained"

for file in data/untrained/*.txt; do
    base=$(basename "$file" .txt)
    output="data/.mem/${base}.mem"

    echo "Training $file → $output"
    ./trainer "$file" "$output"
done

echo "All datasets trained and saved to /data/.mem/"
