cd $(dirname $0)
rm -rf build
mkdir build
cd build && cmake -GNinja -DCMAKE_C_COMPILER=clang-18 -DCMAKE_CXX_COMPILER=clang++-18 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=/home/alex/mipt/cpp-base/third-party/vcpkg/scripts/buildsystems/vcpkg.cmake ..