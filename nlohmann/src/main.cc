#include <map>
#include <mutex>
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
  void set(std::string path, std::string decrypt_key) {
    GlobalSet(path, decrypt_key);
  }
  std::string get(std::string path) {
    return GlobalGet(path);
  }
  void wrongSet(std::string path, std::string decrypt_key) {
//    DecryptAlbum::set(path, decrypt_key);
    emscripten_sync_run_in_main_runtime_thread(
        EM_FUNC_SIG_VII,
        (void *)&SDecryptAlbumSet,
        path.c_str(),
        decrypt_key.c_str()
    );
  }
  std::string wrongGet(std::string path) {
//    return DecryptAlbum::get(path);
    char* res = (char *)emscripten_sync_run_in_main_runtime_thread(
        EM_FUNC_SIG_II, (void *)&SDecryptAlbumGet, path.c_str());
    std::string decrypt_key(res);
    delete res;
    return decrypt_key;
  }
};

EMSCRIPTEN_BINDINGS(map_test_embind) {
    emscripten::class_<MapTestBind>("MapTestBind")
        .constructor<>()
        .function("set", &MapTestBind::set)
        .function("get", &MapTestBind::get)
        .function("wrongSet", &MapTestBind::wrongSet)
        .function("wrongGet", &MapTestBind::wrongGet)
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
