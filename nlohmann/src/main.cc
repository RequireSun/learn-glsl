#include <map>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

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
