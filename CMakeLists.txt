cmake_minimum_required(VERSION 2.8.7) # Travis default

project(delegate CXX)

include(cmake/coverage.cmake)
include(cmake/configure-warnings.cmake)

include_directories(include)

set(SRC src/sample.cpp)
add_executable(sample ${SRC})
add_executable_coverage(coverage_sample ${SRC})
