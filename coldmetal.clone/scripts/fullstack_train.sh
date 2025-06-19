#!/bin/bash

UNTRAINED_DIR="data/untrained"
MEM_DIR="code/data/.mem"
EPOCHS=3

echo "⚙️ Starting Coldmetal Fullstack Training..."

# 1. Step: Convert .txt files into .mem
echo "📥 Embedding raw text files..."
mkdir -p "$MEM_DIR"
for file in "$UNTRAINED_DIR"/*.txt; do
  filename=$(basename -- "$file")
  label="${filename%.txt}"

  echo "🔥 Embedding $filename → $label.mem"
  ./coldmetal__trainer "$file" "$label" "$MEM_DIR/$label.mem"
done

# 2. Step: Build memory index
echo "🧱 Building memory index..."
./memory_builder "$MEM_DIR"

# 3. Step: Train the model
echo "🧠 Training model weights..."
./train_model "$MEM_DIR" "$EPOCHS"

# 4. Step: Confirm weight file
if [ -f "./model.weights" ]; then
  echo "✅ Training complete. Weights saved to model.weights"
else
  echo "❌ ERROR: model.weights not created."
fi

echo "🚀 Coldmetal fullstack pipeline complete."
