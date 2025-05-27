#!/bin/bash

# Helper functions
build() {
  mkdir -p build
  cd build

  if [ ! -f "Makefile" ]; then
    cmake ..
  fi

  make -j$(nproc)
}

run_program() {
  if [ -f "cpp_ants" ]; then
    echo "Running main program..."
    ./cpp_ants
  else
    echo "Executable 'cpp_ants' not found. Build first."
    exit 1
  fi
}

run_tests() {
  echo "Running tests..."
  ctest --output-on-failure -DBUILD_TESTING=ON
}

# Argument handling
case "$1" in
  test)
    build && run_tests
    ;;
  run)
    run_program
    ;;
  build)
    build
    ;;
  "" | *)
    build && run_program
    ;;
esac