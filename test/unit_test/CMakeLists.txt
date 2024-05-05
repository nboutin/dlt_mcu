cmake_minimum_required(VERSION 3.28)
project(dlt_mcu_ut)

include(CTest)
enable_testing()

include(cmake/get_cpm.cmake)
include(cmake/CPM.cmake)
CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  VERSION 1.13.0
  OPTIONS
    "INSTALL_GTEST OFF"
    "gtest_force_shared_crt ON"
)

add_executable(${PROJECT_NAME}
  suites/it_dlt_client.cpp
  $<TARGET_OBJECTS:buffer_mcu>
  $<TARGET_OBJECTS:ring_buffer_mcu>
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    GTest::gmock_main
    test_helper
    dlt_mcu
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
