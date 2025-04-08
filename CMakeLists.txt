cmake_minimum_required(VERSION 3.10)
project(NodeBasedImageEditor)

set(CMAKE_CXX_STANDARD 17)

# Try to find OpenCV
find_package(OpenCV REQUIRED)

# Try to find OpenGL
find_package(OpenGL REQUIRED)

# Try to find GLFW using pkg-config or CMake config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)


# Include directories
include_directories(
    include
    external/imgui
    external/imgui/backends
    external/tinyfiledialogs
    ${OpenCV_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
)

# ImGui sources
file(GLOB IMGUI_SRC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# Project sources
file(GLOB_RECURSE SRC_FILES
    src/core/*.cpp
    src/ui/*.cpp
    src/main.cpp
    external/tinyfiledialogs/tinyfiledialogs.c
)

# Add executable
add_executable(NodeBasedImageEditor ${SRC_FILES} ${IMGUI_SRC})

# Link libraries
target_link_libraries(NodeBasedImageEditor
    ${OpenCV_LIBS}
    ${GLFW_LIBRARY}
    ${OPENGL_gl_LIBRARY}
)

# Compile definitions
add_compile_definitions(GL_SILENCE_DEPRECATION)