cmake_minimum_required(VERSION 3.12)
project(aal_graphs)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES})

add_executable(solve main_solve.cpp ${SOURCES})
add_executable(generate main_generate.cpp ${SOURCES})
add_executable(valve_profiler main_valve_profiler.cpp ${SOURCES})
add_executable(edge_profiler main_edge_profiler.cpp ${SOURCES})
add_executable(solve_tester main_solve_tester.cpp ${SOURCES})
add_executable(unit_tester main_unit_tester.cpp ${SOURCES})