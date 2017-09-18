#!/bin/bash
rm -rf out
mkdir out

BUILD_COMPONENTS_FILE="build_components.txt"
BUILD_COMPONENTS=''

if [ -f $BUILD_COMPONENTS_FILE ]; then
	echo "Found $BUILD_COMPONENTS_FILE"
	while IFS='' read -r line || [[ -n "$LINE" ]]; do
		echo "  Adding $LINE"
		BUILD_COMPONENTS="$BUILD_COMPONENTS $LINE"
	done < $BUILD_COMPONENTS_FILE
fi

echo "Building VEW"
emcc -Isrc $(find . -type f -iname *.cpp -print) $BUILD_COMPONENTS --bind -std=c++11 -O3 -s USE_SDL=2 -s WASM=1 -o out/vew.js
