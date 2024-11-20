cmake_minimum_required(VERSION 3.11)


set(LIB_DIR "lib")
set(SRC_DIR "src")

# Collect all .cpp files in the src/ directory
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")


#Copying assets
file(COPY ${CMAKE_SOURCE_DIR}/Core/res/ DESTINATION ${CMAKE_BINARY_DIR}/res/)

# Add an executable target with all the source files
add_executable(Core ${SOURCES} ${HEADERS})

add_subdirectory("${LIB_DIR}/Glad")
add_subdirectory("${LIB_DIR}/GLFW")


target_include_directories(Core PRIVATE "${LIB_DIR}/Glad/include")
target_include_directories(Core PRIVATE "${LIB_DIR}/GLFW/include")
target_include_directories(Core PRIVATE "${LIB_DIR}/GLM")
target_include_directories(Core PRIVATE "${SRC_DIR}")


# Link libraries (adjust these to match your actual library file names)
target_link_libraries(Core PRIVATE
    glad   # GLEW static
    glfw     # GLFW
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