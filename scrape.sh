#!/bin/bash

url="$1"
id=$(echo "$url" | grep -oP 'epub/\K[0-9]+')
output="data/untrained/book_${id}.txt"

lynx -dump "$url" > "$output"

echo "Scraped $url to $output"
