#!/bin/bash
emcc vew.cpp -O3 -s WASM=1 -o output/vew.html
