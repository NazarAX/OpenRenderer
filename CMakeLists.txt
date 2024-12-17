cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(OpenRenderer)

add_subdirectory("Core")
add_subdirectory("Editor")
add_subdirectory("lib/GLFW")
add_subdirectory("lib/ImGui")
add_subdirectory("lib/TinyFileDialogs")
add_subdirectory("lib/ImGuizmo")