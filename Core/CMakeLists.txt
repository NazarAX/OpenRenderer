cmake_minimum_required(VERSION 3.11)


set(LIB_DIR "lib")
set(SRC_DIR "src")

# Collect all .cpp files in the src/ directory
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")





# Add an executable target with all the source files
add_executable(Core ${SOURCES} ${HEADERS})

target_include_directories(Core PRIVATE "${LIB_DIR}/GLEW/include")
target_include_directories(Core PRIVATE "${LIB_DIR}/GLFW/include")
target_include_directories(Core PRIVATE "${LIB_DIR}/GLM")
target_include_directories(Core PRIVATE "${SRC_DIR}")

target_link_directories(Core PRIVATE
    "${LIB_DIR}/GLEW/lib"
    "${LIB_DIR}/GLFW/lib"
)

# Link libraries (adjust these to match your actual library file names)
target_link_libraries(Core PRIVATE
    glew32s   # GLEW static
    glfw3     # GLFW
    opengl32  # OpenGL (Windows)
)

target_compile_definitions(Core PRIVATE GLEW_STATIC)