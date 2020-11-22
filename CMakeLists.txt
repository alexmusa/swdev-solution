cmake_minimum_required(VERSION 3.10)
project(swdev-solution)

set(CMAKE_CXX_STANDARD 17)

set(WARNING_FLAGS -Wextra -Wall -Wpedantic)
set(DEBUG_FLAGS -g)

set (LIBRAIRIES opencv_core opencv_imgcodecs boost_filesystem boost_system)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# add_subdirectory(lib)
# add_subdirectory(tests)

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/include")
# TODO: Only enable debug flags on debug
target_compile_options(main PRIVATE ${DEBUG_FLAGS} ${WARNING_FLAGS})
target_link_libraries(main PUBLIC ${LIBRAIRIES})