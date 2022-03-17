#!/usr/bin/env bash
set -xe

BASEDIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

rm -f ./build/*.js ./build/*.wasm && mkdir -p ./build/ && cd ./build/
emcmake cmake -DEMSCRIPTEN=YES \
        -DCMAKE_CXX_FLAGS="-s NO_DISABLE_EXCEPTION_CATCHING" \
        ../src/
emmake make -j16
