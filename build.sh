#!/usr/bin/env sh

# Set variables
SOURCE_DIR=$(dirname $(realpath "$0"))
C_COMPILER=$(which cc)
CXX_COMPILER=$(which c++)
NINJA=$(which ninja)
OS=$(uname)

# If OS is Windows, add EXE (.exe) extention
case $OS in
MSYS* | MINGW* | CYGWIN*)
	OS="Windows"
	C_COMPILER="$C_COMPILER.exe"
	CXX_COMPILER="$CXX_COMPILER.exe"
	NINJA="$NINJA.exe"
	;;
esac

echo
echo "------------------------------------------"
echo "OS          : $OS"
echo "Source Dir  : $SOURCE_DIR"
echo "C Compiler  : $C_COMPILER"
echo "CXX Compiler: $CXX_COMPILER"
echo "Ninja       : $NINJA"
echo "------------------------------------------"
echo

# CMake Generate
cmake \
	-S . \
	-B cmake-build \
	-G Ninja \
	-D CMAKE_BUILD_TYPE="Debug" \
	-D CMAKE_C_COMPILER="${C_COMPILER}" \
	-D CMAKE_CXX_COMPILER="${CXX_COMPILER}" \
	-D CMAKE_MAKE_PROGRAM="${NINJA}" \
	-D CMAKE_TOOLCHAIN_FILE="${SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"

# CMake Build
cmake --build cmake-build -j 10
