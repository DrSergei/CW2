#! /bin/sh

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=On -GNinja ..
ninja

echo "Run parallel bfs"
./src/par

echo "Run sequential bfs"
./src/seq

echo "Run tests"
./src/tests
