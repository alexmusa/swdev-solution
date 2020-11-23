cmake_minimum_required(VERSION 3.10)
project(swdev-solution)

set(CMAKE_CXX_STANDARD 14)

set(WARNING_FLAGS -Wextra -Wall -Wpedantic)

set(LIBRARIES opencv_core opencv_imgcodecs boost_filesystem boost_system)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# set(OPENCV_ENABLE_NONFREE)
add_subdirectory(extern/opencv)

add_executable(main main.cpp ${SOURCES})
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_compile_options(main PRIVATE ${WARNING_FLAGS})
target_link_libraries(main PUBLIC ${LIBRARIES})

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()