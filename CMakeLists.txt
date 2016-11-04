cmake_minimum_required(VERSION 3.6)
project(re)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES include/Postfix.h include/Postfix.cpp include/test.h include/State.h include/NFA.h include/NFA.cpp)
add_library(re ${SOURCE_FILES})

add_executable(testPostfix include/testPostfix.cpp)
target_link_libraries(testPostfix re)