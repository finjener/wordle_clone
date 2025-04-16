#!/bin/bash

mkdir -p build_cmake
cd build_cmake

cmake .. -DCMAKE_BUILD_TYPE=Release

cmake --build . -- -j$(nproc)

echo ""
echo "Build completed. To run the application, execute:"
echo "cd src && ./wordle" 