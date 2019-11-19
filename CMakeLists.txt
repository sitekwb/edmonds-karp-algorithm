cmake_minimum_required(VERSION 3.12)
project(aal_graphs)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} main.cpp)

add_executable(aal_graphs ${SOURCES})
