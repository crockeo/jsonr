# Setting up the package.
cmake_minimum_required(VERSION 2.8)
project(jsonr)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/lib")

# Setting the C++11 flag.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Adding the library.
add_library(jsonr "src/parsestream.cpp"
                  "src/streamutils.cpp"
                  "src/parser.cpp"
                  "src/json.cpp"
                  "src/load.cpp")

# Setting up testing.
add_executable(testing "src/testing.cpp")

add_library(testing-lib "src/testing/utils.cpp"
                        "src/testing/00.cpp"
                        "src/testing/01.cpp"
                        "src/testing/02.cpp"
                        "src/testing/03.cpp"
                        "src/testing/04.cpp"
                        "src/testing/05.cpp")

target_link_libraries(testing jsonr testing-lib)

enable_testing()

# Adding in all of the tests.
add_test(parseJSONBool   build/bin/testing 0)
add_test(parseJSONString build/bin/testing 1)
add_test(parseJSONNumber build/bin/testing 2)
add_test(parseJSONArray  build/bin/testing 3)
add_test(parseJSONNull   build/bin/testing 4)
add_test(parseJSONObject build/bin/testing 5)
