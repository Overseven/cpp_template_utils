cmake_minimum_required(VERSION 3.17)
project(test_meta_utils)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_meta_utils examples/abstract.cpp func_abstract.h common.h func_alias.h examples/alias.cpp main.cpp)