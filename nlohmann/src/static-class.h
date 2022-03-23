//
// Created by bytedance on 2022/3/23.
//

#ifndef LEARN_GLSL_STATIC_CLASS_H
#define LEARN_GLSL_STATIC_CLASS_H

extern "C" {
  static std::map<std::string, std::string> m_map;
  class DecryptAlbum {
  public:
    static void set(const std::string path, const std::string decrypt_key) {
      m_map[path] = decrypt_key;
    }
    static std::string get(const std::string &path) {
      auto iter = m_map.find(path);
      std::string ret = iter == m_map.end() ? "" : iter->second;
      return ret;
    }
  };
};

#endif //LEARN_GLSL_STATIC_CLASS_H
