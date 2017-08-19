#!/bin/bash
emcc src/*.cpp -std=c++11 -O3 -s WASM=1 -o out/vew.html