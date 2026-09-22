cmake_minimum_required(VERSION 3.28)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(render src/main.cpp)
target_include_directories(render PRIVATE include)
target_compile_options(render PRIVATE -Wall -Wextra -Wpedantic -Werror -ferror-limit=0)

add_executable(vec3_test tests/vec3_test.cpp)
target_include_directories(vec3_test PRIVATE include)
target_compile_options(vec3_test PRIVATE -Wall -Wextra -Wpedantic -Werror -ferror-limit=0)
