//
// Created by bytedance on 2022/3/23.
//

#ifndef LEARN_GLSL_STATIC_CLASS_H
#define LEARN_GLSL_STATIC_CLASS_H

//static std::mutex mtx;
//
//class DecryptAlbum {
//public:
//  static std::map<std::string, std::string> m_map;
//  static void set(const std::string path, const std::string decrypt_key) {
//    mtx.lock();
//    m_map[path] = decrypt_key;
//    mtx.unlock();
//  }
//  static std::string get(const std::string &path) {
//    mtx.lock();
//    auto iter = m_map.find(path);
//    std::string ret = iter == m_map.end() ? "" : iter->second;
//    mtx.unlock();
//    return ret;
//  }
//};

extern "C" {
  static std::map<std::string, std::string> m_map;
  static void DecryptAlbumSet(const std::string path, const std::string decrypt_key) {
    m_map[path] = decrypt_key;
  }
  static std::string DecryptAlbumGet(const std::string &path) {
    auto iter = m_map.find(path);
    std::string ret = iter == m_map.end() ? "" : iter->second;
    return ret;
  }
};

static void SDecryptAlbumSet(char *path, char *decrypt_key) {
  std::string s_path(path);
  std::string s_decrypt_key(decrypt_key);
//  DecryptAlbum::set(s_path, s_decrypt_key);
  DecryptAlbumSet(s_path, s_decrypt_key);
}

static char* SDecryptAlbumGet(char *path) {
  std::string s_path(path);
//  std::string ret = DecryptAlbum::get(s_path);
  std::string ret = DecryptAlbumGet(s_path);
  char* value = new char[ret.length() + 1];
  strcpy(value, ret.c_str());
  return value;
}

#endif //LEARN_GLSL_STATIC_CLASS_H
