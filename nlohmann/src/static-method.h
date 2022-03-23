//
// Created by bytedance on 2022/3/23.
//

#ifndef LEARN_GLSL_STATIC_METHOD_H
#define LEARN_GLSL_STATIC_METHOD_H

static std::map<std::string, std::string> global_m_map;
static void GlobalSet(const std::string path, const std::string decrypt_key) {
  global_m_map[path] = decrypt_key;
}

static std::string GlobalGet(const std::string &path) {
  auto iter = global_m_map.find(path);
  return iter == global_m_map.end() ? "" : iter->second;
}


#endif //LEARN_GLSL_STATIC_METHOD_H
