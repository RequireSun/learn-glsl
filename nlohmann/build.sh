#!/usr/bin/env bash
set -xe

BASEDIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

rm -f ./build/*.js ./build/*.wasm && mkdir -p ./build/ && cd ./build/
emcmake cmake -DEMSCRIPTEN=YES \
        -DCMAKE_CXX_FLAGS="-s NO_DISABLE_EXCEPTION_CATCHING \
                           -s USE_PTHREADS=1 \
                           -s PTHREAD_POOL_SIZE=30 \
                           -s ALLOW_MEMORY_GROWTH=1 \
                           -s ASSERTIONS=1 \
                           -s SAFE_HEAP=1 \
                           -O0 \
                           -g4 \
                           --js-opts 0 \
                           --memoryprofiler \
                           --cpuprofiler \
                           -gseparate-dwarf=index.debug.wasm \
                           -s SEPARATE_DWARF_URL=http://localhost:8877/build/index.debug.wasm \
                           --source-map-base http://127.0.0.1:8877/build/ \
                           --bind" \
        ../src/
emmake make -j16
