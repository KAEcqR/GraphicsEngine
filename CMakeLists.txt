cmake_minimum_required(VERSION 3.20)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)

FetchContent_MakeAvailable(glfw)

# GLAD
add_library(glad Source/glad.c
        Headers/shaderClass.h
        Source/shaderClass.cpp
        Headers/VBO.h
        Source/VBO.cpp
        Headers/VAO.h
        Source/VAO.cpp)
target_include_directories(glad PUBLIC Libraries/include)

include_directories(${PROJECT_SOURCE_DIR}/Headers)

# folder źródłowy shaderów
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/Shaders")

# folder docelowy w build
set(BUILD_SHADERS_DIR "${CMAKE_BINARY_DIR}/Shaders")

# kopiowanie wszystkich plików z folderu Shaders
file(GLOB SHADER_FILES "${SHADERS_DIR}/*.vert" "${SHADERS_DIR}/*.frag")

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${BUILD_SHADERS_DIR}/${FILE_NAME} COPYONLY)
endforeach()

# Executable
add_executable(GraphicsEngine Source/main.cpp)

# Linkowanie (po utworzeniu targetu!)
target_link_libraries(GraphicsEngine
        glfw
        glad
        opengl32
)