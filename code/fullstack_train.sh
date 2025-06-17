#!/bin/bash

MEM_DIR="../data/.mem"
EPOCHS=3

echo "⚙️ Starting Coldmetal Fullstack Training..."

# 1. Step: Vectorize all raw .mem files
echo "📦 Embedding memory files..."
for file in "$MEM_DIR"/*.mem; do
  if grep -q "\"vector\":" "$file"; then
    echo "🟡 Already embedded: $(basename "$file")"
    continue
  fi

  filename=$(basename -- "$file")
  label="${filename%.mem}"

  echo "🔥 Embedding $filename..."
  ./coldmetal__trainer "$file" "$label" "$file"
done

# 2. Step: Run memory builder
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
