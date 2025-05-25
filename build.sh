#!/bin/bash

# Create build dir if it doesn't exist
mkdir -p build
cd build

# Configure (only if CMakeFiles don't exist)
if [ ! -f "Makefile" ]; then
  cmake ..
fi

# Build project
make -j$(nproc)

# Run the program if build was successful
if [ $? -eq 0 ]; then
  echo "Build successful. Running program..."
  ./cpp_ants
else
  echo "Build failed."
fi