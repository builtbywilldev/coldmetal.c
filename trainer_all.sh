#!/bin/bash

echo "🚀 Starting batch training from /data/untrained"

shopt -s nullglob  # avoid issues if no files found

for file in data/untrained/*.{txt,json}; do
    base=$(basename "$file")
    name="${base%.*}"
    output="data/.mem/${name}.mem"

    echo "📚 Training $file → $output"
    ./train "$file" "$output"
done

echo "✅ All datasets trained and saved to /data/.mem/"
