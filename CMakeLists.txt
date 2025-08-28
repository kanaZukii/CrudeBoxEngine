cmake_minimum_required(VERSION 3.15)
project(CrudeBoxEngine)
set(CMAKE_CXX_STANDARD 17)

# Set global runtime output path for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)

# Vendor dependencies
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Enable Wayland support")
set(GLFW_BUILD_X11 ON CACHE BOOL "Enable X11 support")

add_subdirectory(extern/glfw)

add_library(glad extern/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/include)

add_library(imgui
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    extern/imgui
    extern/imgui/backends
    ${CMAKE_SOURCE_DIR}/extern/glfw/include 
)

add_subdirectory(extern/openal-soft)
add_subdirectory(Engine)
add_subdirectory(Editor)
# add_subdirectory(Sandbox) # For later use
