cmake_minimum_required(VERSION 3.25.0)
project(imgui)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")



add_library(imgui STATIC ${SOURCES} ${HEADERS})

target_include_directories(imgui PUBLIC "../GLFW/include")

target_link_libraries(imgui PRIVATE glfw)
