cmake_minimum_required(VERSION 3.28)
project(${PROJECT_NAME}_test LANGUAGES C CXX)

set(comp_NAME dlt_mcu)

# Get include directories from target
get_target_property(comp_INC_DIR ${comp_NAME} INCLUDE_DIRECTORIES)

# Get sources files list from target
get_target_property(comp_SOURCES_TMP ${comp_NAME} SOURCES)
foreach(item ${comp_SOURCES_TMP})
  list(APPEND comp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/../../${item})
endforeach()

# Get link libraries from target
get_target_property(comp_LINK_LIBRARIES ${comp_NAME} LINK_LIBRARIES)

# Get compile definitions from target
get_target_property(comp_COMPILE_DEFINITIONS ${comp_NAME} COMPILE_DEFINITIONS)

add_cutie_test_target(
  NAME ${PROJECT_NAME}
  TEST suites/it_dlt_client.cpp
  SOURCES
    ${comp_SOURCES}
    $<TARGET_OBJECTS:buffer_mcu>
    $<TARGET_OBJECTS:ring_buffer_mcu>
  INCLUDE_DIRECTORIES ${comp_INC_DIR}
  LINK_LIBRARIES ${comp_LINK_LIBRARIES} test_helper
)

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})
