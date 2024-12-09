cmake_minimum_required(VERSION 3.11)


set(LIB_DIR "lib")
set(GLOB_LIB_DIR "../lib")
set(SRC_DIR "src")

# Collect all .cpp files in the src/ directory
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")



# Add an executable target with all the source files
add_library(Core STATIC ${SOURCES} ${HEADERS})

#file(COPY ${CMAKE_SOURCE_DIR}/Core/res DESTINATION  ${CMAKE_BINARY_DIR}/Core)
#


add_subdirectory("${LIB_DIR}/Glad")
add_subdirectory("${LIB_DIR}/Assimp")
add_subdirectory("${LIB_DIR}/yaml-cpp")

#including subdirectory library dependepcies
target_include_directories(Core PRIVATE "${LIB_DIR}/Assimp/include")
target_include_directories(Core PRIVATE "${LIB_DIR}/Glad/include")
target_include_directories(Core PRIVATE "${LIB_DIR}/yaml-cpp/include")
#including global library dependencies
target_include_directories(Core PRIVATE "${GLOB_LIB_DIR}/GLM")
target_include_directories(Core PRIVATE "${GLOB_LIB_DIR}/GLFW/include")
target_include_directories(Core PRIVATE "${GLOB_LIB_DIR}/ImGui")
target_include_directories(Core PRIVATE "${GLOB_LIB_DIR}/entt")
#including project sources 
target_include_directories(Core PRIVATE "${SRC_DIR}")


# Link libraries (adjust these to match your actual library file names)
target_link_libraries(Core PRIVATE
        assimp
        glad   # GLEW static
        glfw     # GLFW
        imgui
        yaml-cpp
)

if (APPLE)
target_link_libraries(Core PRIVATE
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework QuartzCore"
)
endif()

if (WIN32)
target_link_libraries(Core PRIVATE
    opengl32
)
endif()

target_compile_definitions(Core PRIVATE GLEW_STATIC)