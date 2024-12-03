cmake_minimum_required(VERSION 3.11)


set(SRC_DIR "src")

# Collect all .cpp files in the src/ directory
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")



# Add an executable target with all the source files
add_executable(Editor ${SOURCES} ${HEADERS})


target_include_directories(Editor PRIVATE "../Core/src")
target_include_directories(Editor PRIVATE "../lib/GLM")
target_include_directories(Editor PRIVATE "../lib/ImGui")
target_include_directories(Editor PRIVATE "../lib/entt")



target_link_libraries(Editor PRIVATE Core imgui)
#file(COPY ${CMAKE_SOURCE_DIR}/Core/res DESTINATION  ${CMAKE_BINARY_DIR}/Core)
#
