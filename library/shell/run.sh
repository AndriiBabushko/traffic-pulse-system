#!/bin/bash

cd ..

echo "🚀 Build up CMake..."
make build

echo "🚀 Compiling..."
make compile

echo "🚀 Running simulation..."
make run

echo "🚀 Cleaning up..."
make clean

cd shell/ || exit
