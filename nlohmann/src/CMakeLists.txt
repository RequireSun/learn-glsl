CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
include(FetchContent)
set(CMAKE_CXX_STANDARD 14)

PROJECT(nlohmann_test)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)
#FIND_PACKAGE(nlohmann_json 3.10.5 REQUIRED)

AUX_SOURCE_DIRECTORY(. SRC_LIST) #将./下的所有*.cpp加入到SRC_LIST中
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../build)
ADD_EXECUTABLE(index ${SRC_LIST})
TARGET_LINK_LIBRARIES(index PRIVATE nlohmann_json::nlohmann_json)

