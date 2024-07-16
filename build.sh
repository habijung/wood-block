#!/usr/bin/env sh

# CMake Generate
cmake \
    -S . \
    -B cmake-build \
    -G Ninja \
    -D CMAKE_BUILD_TYPE="Debug"

# CMake Build
cmake --build cmake-build -j 10
