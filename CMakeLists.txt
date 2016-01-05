# Setting up the package.
cmake_minimum_required(VERSION 2.8)
project(jsonr)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/")

# Setting the C++11 flag.
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O2 ${CMAKE_CXX_FLAGS}")

# Adding the library.
set(JSONR_SOURCES src/jsonr/parseexception.cpp
                  src/jsonr/parsestream.cpp
                  src/jsonr/streamutils.cpp
                  src/jsonr/parser.cpp
                  src/jsonr/json.cpp
                  src/jsonr/load.cpp)

add_library(jsonr SHARED ${JSONR_SOURCES})

# Setting up testing.
add_executable(testing src/testing/testing.cpp)

set(TESTING_LIB_SOURCES src/testing/utils.cpp
                        src/testing/00.cpp
                        src/testing/01.cpp
                        src/testing/02.cpp
                        src/testing/03.cpp
                        src/testing/04.cpp
                        src/testing/05.cpp)

add_library(testing-lib ${TESTING_LIB_SOURCES})

target_link_libraries(testing jsonr testing-lib)

enable_testing()

# Adding in all of the tests.
add_test(parseJSONBool   build/testing 0)
add_test(parseJSONString build/testing 1)
add_test(parseJSONNumber build/testing 2)
add_test(parseJSONArray  build/testing 3)
add_test(parseJSONNull   build/testing 4)
add_test(parseJSONObject build/testing 5)

# Adding installation.
install(TARGETS jsonr
        LIBRARY DESTINATION lib)

install(DIRECTORY src/jsonr/
        DESTINATION include/jsonr
        FILES_MATCHING PATTERN *.hpp)

install(FILES src/cmake/Findjsonr.cmake
        DESTINATION "${CMAKE_ROOT}/Modules")
