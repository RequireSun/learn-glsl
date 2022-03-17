#!/usr/bin/env bash
set -xe

BASEDIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

rm -rf ./build && mkdir ./build && cd ./build
emcmake cmake -DCMAKE_CXX_FLAGS="-o ${BASEDIR}/build/index.html \
              -std=c++14" \
              ../src/
emmake make -j16
