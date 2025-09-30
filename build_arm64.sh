#!/bin/bash

readonly BUILD_DIR="$(pwd)/build"

if [[ $1 == "-d" ]]; then
	rm -rf "$BUILD_DIR"
fi

if [ ! -d "$BUILD_DIR" ]; then
	mkdir -p "$BUILD_DIR"
	cmake -DCMAKE_TOOLCHAIN_FILE=cmake/aarch64-linux-gnu.cmake -B build -S .
fi

make -C build -j $(nproc)
