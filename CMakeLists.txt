cmake_minimum_required(VERSION 3.12)
project(aal_graphs)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES})

add_executable(solve main_solve.cpp ${SOURCES})
add_executable(generate main_generate.cpp ${SOURCES})
add_executable(valve_tester main_valve_tester.cpp ${SOURCES})
add_executable(edge_tester main_edge_tester.cpp ${SOURCES})