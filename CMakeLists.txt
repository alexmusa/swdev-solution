cmake_minimum_required(VERSION 3.10)
project(swdev-solution)

set(CMAKE_CXX_STANDARD 17)

set(WARNING_FLAGS -Wextra -Wall -Wpedantic)

set(LIBRARIES opencv_core opencv_imgcodecs boost_filesystem boost_system)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(main main.cpp ${SOURCES})
target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_compile_options(main PRIVATE ${WARNING_FLAGS})
target_link_libraries(main PUBLIC ${LIBRARIES})

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()