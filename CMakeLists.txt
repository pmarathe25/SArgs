cmake_minimum_required(VERSION 3.10)
include(../utils.cmake)
project(SArgs)

# Add install target for interface.
add_install_header(include/interfaces/SArgs)
add_uninstall()

# Add SArgs lib
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(sargs SHARED ${SOURCE_FILES})

# Add test executable
add_executable(test0 test/test.cpp)
target_link_libraries(test0 sargs)
enable_testing()
add_test(NAME test COMMAND ${CMAKE_BINARY_DIR}/test0)
