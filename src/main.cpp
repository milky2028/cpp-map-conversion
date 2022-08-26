#include <emscripten/bind.h>
#include <boost/optional.hpp>
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

using clipboard_t = std::map<std::string, boost::optional<clipboard_entry>>;

class Application {
 private:
   clipboard_t _clipboard_data;
 public:  
  // bool clipboard_needs_data() { return true; }

  auto clipboard() {
    return _clipboard_data;
  }
};

auto expose_buffer(const clipboard_entry& entry) {
  const auto ptr = static_cast<uint8_t*>(entry._buffer.get());
  return emscripten::val(emscripten::typed_memory_view(entry._size, ptr));
}

// template <class T>
// T unwrap_optional(boost::optional<T> optional) {
//   if (optional) {
//     return optional.get();
//   }

//   return T {}; 
// }

auto get_clipboard(Application& app) {
  auto entries = app.clipboard();
  std::map<std::string, emscripten::val> consumable_entries;

  for (const auto &[type, entry] : entries) {
    if (entry) {
      auto unwrapped_entry = entry.get();
      consumable_entries[type] = expose_buffer(unwrapped_entry);
    } else {
      consumable_entries[type] = emscripten::val::null();
    }
  }

  return consumable_entries;
}

auto set_clipboard(Application& app, std::string item_type, size_t buffer_size, uint32_t ptr_to_buffer) {
  auto entries = app.clipboard();
  auto ptr = reinterpret_cast<uint8_t*>(ptr_to_buffer);

  boost::optional<clipboard_entry> new_entry = clipboard_entry {
    ._buffer = std::shared_ptr<void>(ptr),
    ._size = buffer_size
  };
  
  entries[item_type] = new_entry;
}

EMSCRIPTEN_BINDINGS(Application) {
  emscripten::class_<Application>("Application")
      .constructor()
      // .function("clipboard_needs_data", &Application::clipboard_needs_data)
      .function("get_clipboard", &get_clipboard)
      .function("set_clipboard", &set_clipboard);

  emscripten::register_map<std::string, emscripten::val>("Application$ClipboardEntry$Map");
  // emscripten::register_vector<std::string>("Application$ClipboardMap$Keys");
}