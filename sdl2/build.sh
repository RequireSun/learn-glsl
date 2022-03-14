#!/usr/bin/env bash
set -xe

rm -rf ./build && mkdir ./build
emcc main.cc -o ./build/index.html -s USE_SDL=2
