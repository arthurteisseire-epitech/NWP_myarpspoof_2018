cmake_minimum_required(VERSION 3.12)
project(myARPspoof CXX C)

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE sources src/*.c include/*.h)
file(GLOB_RECURSE tests tests/*.c)
add_executable(${CMAKE_PROJECT_NAME} ${sources} ${tests})
target_link_libraries(${CMAKE_PROJECT_NAME} criterion)
