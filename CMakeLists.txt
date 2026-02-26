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
add_library(glad glad.c)
target_include_directories(glad PUBLIC Libraries/include)

# Executable
add_executable(GraphicsEngine main.cpp)

# Linkowanie (po utworzeniu targetu!)
target_link_libraries(GraphicsEngine
        glfw
        glad
        opengl32
)