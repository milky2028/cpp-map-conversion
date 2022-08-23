#include <emscripten/bind.h>
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
class Application {
 public:
  auto clipboard() {
    clipboard_entry clippy{
        ._buffer = std::shared_ptr<char>(new char[5]),
        ._size = 5,
    };

    return clippy;
  }
};

EMSCRIPTEN_BINDINGS(Application) {
  emscripten::class_<clipboard_entry>("ClipboardEntry")
      .property("_buffer", &clipboard_entry::_buffer)
      .property("_size", &clipboard_entry::_size);

  emscripten::class_<Application>("Application")
      .constructor()
      .function("clipboard", &Application::clipboard);
}