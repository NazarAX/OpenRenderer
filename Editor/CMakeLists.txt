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
target_include_directories(Editor PRIVATE "../lib/TinyFileDialogs")
target_include_directories(Editor PRIVATE "../lib/ImGuizmo")



target_link_libraries(Editor PRIVATE Core imgui tfd imguizmo)

add_custom_target(CopyRes
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Editor/res/
        ${CMAKE_BINARY_DIR}/Editor/res
        COMMENT "Copying resource files to ${CMAKE_BINARY_DIR}/Core/res/"
)

add_dependencies(Editor CopyRes)