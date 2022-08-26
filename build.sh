rm -rf ./build && mkdir build
emcc -s MODULARIZE=1 \
src/main.cpp -lembind -I /Users/tgross/Downloads/boost -o build/lib.js -std=c++17