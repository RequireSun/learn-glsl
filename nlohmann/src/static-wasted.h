//
// Created by bytedance on 2022/3/24.
//

#ifndef LEARN_GLSL_STATIC_WASTED_H
#define LEARN_GLSL_STATIC_WASTED_H

#include <mutex>
// mutex + run_in_main 都不行

static std::mutex mtx;

class DecryptAlbum {
public:
  static std::map<std::string, std::string> m_map;
  static void set(const std::string path, const std::string decrypt_key) {
    mtx.lock();
    m_map[path] = decrypt_key;
    mtx.unlock();
  }
  static std::string get(const std::string &path) {
    mtx.lock();
    auto iter = m_map.find(path);
    std::string ret = iter == m_map.end() ? "" : iter->second;
    mtx.unlock();
    return ret;
  }
};

static void SDecryptAlbumSet(char *path, char *decrypt_key) {
  std::string s_path(path);
  std::string s_decrypt_key(decrypt_key);
  DecryptAlbum::set(s_path, s_decrypt_key);
}

static char* SDecryptAlbumGet(char *path) {
  std::string s_path(path);
  std::string ret = DecryptAlbum::get(s_path);
  char* value = new char[ret.length() + 1];
  strcpy(value, ret.c_str());
  return value;
}

class MapTestBind {
public:
  void wrongSet(std::string path, std::string decrypt_key) {
    emscripten_sync_run_in_main_runtime_thread(
        EM_FUNC_SIG_VII,
        (void *) &SDecryptAlbumSet,
        path.c_str(),
        decrypt_key.c_str()
    );
  }

  std::string wrongGet(std::string path) {
    char *res = (char *) emscripten_sync_run_in_main_runtime_thread(
        EM_FUNC_SIG_II, (void *) &SDecryptAlbumGet, path.c_str());
    std::string decrypt_key(res);
    delete res;
    return decrypt_key;
  }
}

#endif //LEARN_GLSL_STATIC_WASTED_H
