cmake_minimum_required(VERSION 3.6)
project(re)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES include/Postfix.h Postfix.cpp include/test.h include/State.h include/NFA.h NFA.cpp include/DFA.h DFA.cpp)
add_library(re ${SOURCE_FILES})

add_executable(testDFA testDFA.cpp)
target_link_libraries(testDFA re)

add_executable(testPostfix testPostfix.cpp)
target_link_libraries(testPostfix re)