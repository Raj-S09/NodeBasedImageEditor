cmake_minimum_required(VERSION 3.10)
project(NodeEditorApp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

file(GLOB_RECURSE SRC_FILES src/core/*.cpp)

add_executable(NodeEditorApp ${SRC_FILES} src/main.cpp)

target_link_libraries(NodeEditorApp ${OpenCV_LIBS})