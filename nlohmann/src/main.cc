#include <map>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <emscripten/threading.h>
#include "static-method.h"
#include "static-class.h"

class MapTestBind {
public:
  void GlobalSet(std::string path, std::string decrypt_key) {
    _GlobalSet(path, decrypt_key);
  }
  std::string GlobalGet(std::string path) {
    return _GlobalGet(path);
  }
  void NamedSet(std::string path, std::string decrypt_key) {
    ns::DecryptAlbum::set(path, decrypt_key);
  }
  std::string NamedGet(std::string path) {
    return ns::DecryptAlbum::get(path);
  }
};

EMSCRIPTEN_BINDINGS(map_test_embind) {
    emscripten::class_<MapTestBind>("MapTestBind")
        .constructor<>()
        .function("GlobalSet", &MapTestBind::GlobalSet)
        .function("GlobalGet", &MapTestBind::GlobalGet)
        .function("NamedSet", &MapTestBind::NamedSet)
        .function("NamedGet", &MapTestBind::NamedGet)
    ;
}

int main() {
  std::string json_str = "{ \"test\": \"abc\" }";
  std::cout << "hello world" << std::endl;

  try {
    nlohmann::json json_obj = nlohmann::json::parse(json_str);
    std::cout << "read property from nlohmann object: " << json_obj["test"].get<std::string>() << std::endl;
    std::map<std::string, std::string> obj = json_obj;
    std::cout << "read property from std::map object: " << obj["test"] << std::endl;
  } catch (const std::exception &exception) {
    std::cerr << exception.what() << std::endl;
  }

  return 0;
}
