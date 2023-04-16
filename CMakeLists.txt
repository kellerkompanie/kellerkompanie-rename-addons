cmake_minimum_required(VERSION 3.18)

project(keko-rename)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(kekorename src/main.cpp)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")