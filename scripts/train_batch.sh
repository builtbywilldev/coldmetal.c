#!/bin/bash

MEM_DIR="../data/.mem"

for file in "$MEM_DIR"/*.mem; do
  filename=$(basename -- "$file")
  label="${filename%.mem}"
  echo "🔥 Training $filename with label '$label'..."

  ./coldmetal__trainer "$file" "$label" "$file"

  if [ $? -eq 0 ]; then
    echo "✅ $filename embedded and saved."
  else
    echo "❌ Failed on $filename"
  fi
done
