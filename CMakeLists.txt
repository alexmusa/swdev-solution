cmake_minimum_required(VERSION 3.10)
project(swdev-solution)

set(CMAKE_CXX_STANDARD 14)

set(WARNING_FLAGS -Wextra -Wall -Wpedantic)

set(LIBRARIES opencv_core opencv_imgcodecs boost_filesystem boost_system)
set(OPENCV_DEFAULT_INCLUDE_DIR "/usr/local/include/opencv4")
set(OPENCV_DEFAULT_LIB_DIR "/usr/local/lib")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_library(OPENCV_CORE 
    NAMES opencv_core 
    PATHS ${OPENCV_DEFAULT_LIB_DIR} ${OPENCV_DEFAULT_INCLUDE_DIR})
find_library(OPENCV_IMGCODECS 
    NAMES opencv_imgcodecs 
    PATHS ${OPENCV_DEFAULT_LIB_DIR}  ${OPENCV_DEFAULT_INCLUDE_DIR})

message(STATUS "Library found: ${OPENCV_CORE}")
message(STATUS "Library found: ${OPENCV_IMGCODECS}")

add_executable(main main.cpp ${SOURCES})
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/include"
                                PRIVATE "${OPENCV_DEFAULT_INCLUDE_DIR}")

target_compile_options(main PRIVATE ${WARNING_FLAGS})
target_link_libraries(main PUBLIC ${LIBRARIES})

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()