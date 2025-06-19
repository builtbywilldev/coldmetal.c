#!/bin/bash
gcc -Iinclude src/main.c src/tokenizer.c src/logic.c src/memory.c src/embedder.c src/attention.c -o morpheus -lm
gcc -Iinclude src/trainer.c src/tokenizer.c src/memory.c src/embedder.c -o trainer -lm
