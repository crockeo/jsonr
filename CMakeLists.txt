# Setting up the package.
cmake_minimum_required(VERSION 2.8)
project(jsonr)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/lib")

# Setting the C++11 flag.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Adding the executable.
add_library(jsonr "src/parser.cpp"
                  "src/json.cpp"
                  "src/load.cpp")
