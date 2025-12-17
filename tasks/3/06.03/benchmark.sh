#!/bin/bash

COMPILER=clang++-18
FLAGS="-std=c++20 -O2"
TIME_CMD="/usr/bin/time -f %e"

SRC_HEADERS="$1/../06.01"
SRC_MODULES="$1/../06.02"

echo "=================================================="
echo "Benchmark: Headers vs Modules (Clang 18)"
echo "=================================================="

mkdir -p benchmark_build
cd benchmark_build

# ==============================================================================
# 1. Сборка решения на ХЕДЕРАХ (06.01)
# ==============================================================================
echo
echo "[ HEADERS APPROACH (06.01) ]"
mkdir -p build_headers
cd build_headers

echo -n "1. Compiling Rational.cpp ... "
$TIME_CMD $COMPILER $FLAGS -c $SRC_HEADERS/Rational.cpp -I $SRC_HEADERS -o Rational.o

echo -n "2. Compiling main.cpp ...     "
$TIME_CMD $COMPILER $FLAGS -c $SRC_HEADERS/main.cpp -I $SRC_HEADERS -o main.o

echo -n "3. Linking ...                "
$TIME_CMD $COMPILER Rational.o main.o -o app_headers

echo
echo "--- Sizes (Headers) ---"
echo "Object files:"
du -h Rational.o main.o
echo
echo "Executable:"
du -h app_headers

cd ..

# ==============================================================================
# 2. Сборка решения на МОДУЛЯХ (06.02)
# ==============================================================================
echo
echo "[ MODULES APPROACH (06.02) ]"
mkdir -p build_modules
cd build_modules

MOD_PARTITION="$SRC_MODULES/rational_mixins.cppm"
MOD_INTERFACE="$SRC_MODULES/rational.cppm"
MOD_IMPL="$SRC_MODULES/rational.cpp"
MAIN_SRC="$SRC_MODULES/main.cpp"

echo "1. Building Partition (rational:mixins)..."

echo -n "   a) Precompile (.pcm) ...   "
$TIME_CMD $COMPILER $FLAGS --precompile $MOD_PARTITION -o rational_mixins.pcm

echo -n "   b) Compile object (.o) ... "
$TIME_CMD $COMPILER $FLAGS -c rational_mixins.pcm -o rational_mixins.o


echo "2. Building Interface (rational)..."

echo -n "   a) Precompile (.pcm) ...   "
$TIME_CMD $COMPILER $FLAGS --precompile $MOD_INTERFACE \
    -fmodule-file=rational:mixins=rational_mixins.pcm \
    -o rational.pcm

echo -n "   b) Compile object (.o) ... "
$TIME_CMD $COMPILER $FLAGS -c rational.pcm \
    -fmodule-file=rational:mixins=rational_mixins.pcm \
    -o rational_interface.o


echo -n "3. Compiling Rational.cpp ... "
$TIME_CMD $COMPILER $FLAGS -c $MOD_IMPL \
    -fmodule-file=rational=rational.pcm \
    -fmodule-file=rational:mixins=rational_mixins.pcm \
    -o rational_impl.o


echo -n "4. Compiling main.cpp ...     "
$TIME_CMD $COMPILER $FLAGS -c $MAIN_SRC \
    -fmodule-file=rational=rational.pcm \
    -fmodule-file=rational:mixins=rational_mixins.pcm \
    -o main.o


echo -n "5. Linking ...                "
$TIME_CMD $COMPILER rational_mixins.o rational_interface.o rational_impl.o main.o -o app_modules


echo
echo "--- Sizes (Modules) ---"
echo "BMI (PCM) files:"
du -h rational_mixins.pcm rational.pcm
echo
echo "Object files:"
du -h rational_mixins.o rational_interface.o rational_impl.o main.o
echo
echo "Executable:"
du -h app_modules

cd ..

echo
echo "Done."
