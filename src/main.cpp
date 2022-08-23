#include <emscripten/bind.h>
#include <iostream>
#include <map>
#include <memory>

class Application {
 public:
  bool clipboard() { return true; }
};

EMSCRIPTEN_BINDINGS(Application) {
  emscripten::class_<Application>("Application")
      .constructor()
      .function("clipboard", &Application::clipboard);
}