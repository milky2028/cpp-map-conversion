alias do-build="clang src/main.cpp -Wall -Wextra -Werror -std=c++17 -lstdc++ -ggdb3 -o build/app.o -lm"
alias run="./build/app.o"
alias build_and_run="do-build && run"