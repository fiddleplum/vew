#!/bin/bash
rm out/*
emcc src/*.cpp -std=c++11 -O3 -s USE_SDL=2 -s WASM=1 -o out/vew.js