#!/bin/bash

rm -rf build
mkdir build
cd build

export CC=clang-18
export CXX=clang++-18

cmake .. -G Ninja

ninja