cmake_minimum_required(VERSION 3.12)
project(aal_graphs)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES})

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})


add_executable(solve main_solve.cpp ${SOURCES})
add_executable(generate main_generate.cpp ${SOURCES})
add_executable(valve_profiler main_valve_profiler.cpp ${SOURCES})
add_executable(edge_profiler main_edge_profiler.cpp ${SOURCES})
add_executable(solve_tester main_solve_tester.cpp ${SOURCES})
add_executable (Boost_Tests_run boost_tests/test.cpp ${SOURCES})

target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})
