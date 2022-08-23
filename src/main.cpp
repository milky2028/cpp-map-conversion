#include <iostream>
#include <map>
#include <memory>

struct clipboard_entry {
    std::shared_ptr<void> _buffer;
    std::size_t _size{0};

    friend bool operator==(const clipboard_entry& x, const clipboard_entry& y) {
        return x._buffer == y._buffer && x._size == y._size;
    }

    friend bool operator!=(const clipboard_entry& x, const clipboard_entry& y) {
        return !(x == y);
    }
};

using clipboard_t = std::map<std::string, int>;

int main() {
  std::map<std::string, int> some_map {{"one", 1}, {"two", 2}, { "three", 3}};
  std::cout << some_map["two"] << std::endl;
}