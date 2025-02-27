#!/bin/bash

./run.sh

fswatch -o src/ include/ | while read num; do
    echo "🔄 Changes found. Recompiling..."
    ninja && ./simulation_test
done
