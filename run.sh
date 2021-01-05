mkdir -p build
cd build
cmake -I/lib ..
cmake --build . && ./main
