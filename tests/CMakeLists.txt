# Modified from https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

macro(package_add_test TESTNAME FILES)
    add_executable(${TESTNAME} ${FILES} ${SOURCES})
    target_include_directories(${TESTNAME} PRIVATE "${PROJECT_SOURCE_DIR}/include"
                                           PRIVATE "${OPENCV_DEFAULT_INCLUDE_DIR}")
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})

    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(data_test "data_test.cpp")
