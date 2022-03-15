#!/usr/bin/env bash
set -xe

rm -rf ./build && mkdir ./build
emcc main.cc events.cc camera.cc -o ./build/index.html \
  -std=c++14 \
  -s GL_DEBUG=1 \
  -s FULL_ES2=1 \
  -s FULL_ES3=1 \
  -s USE_WEBGL2=1 \
  -s USE_GLFW=3 \
  -s USE_SDL=2 \
  -s USE_SDL_IMAGE=2 \
  -s SDL2_IMAGE_FORMATS='["png"]'
