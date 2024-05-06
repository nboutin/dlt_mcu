cmake_minimum_required(VERSION 3.28)
project(dlt_mcu_ut)

include(cmake/get_cpm.cmake)
include(cmake/CPM.cmake)

CPMAddPackage(
  NAME cutie
  GITHUB_REPOSITORY nboutin/Cutie
  VERSION task/use_cpm
)

get_filename_component(CUTIE_DIR ${cutie_SOURCE_DIR} REALPATH)
include(${cutie_SOURCE_DIR}/cutie.cmake)

# ---
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

# add_executable(${PROJECT_NAME}
#   suites/it_dlt_client.cpp
#   $<TARGET_OBJECTS:buffer_mcu>
#   $<TARGET_OBJECTS:ring_buffer_mcu>
# )

# target_link_libraries(${PROJECT_NAME}
#   PRIVATE
#     GTest::gmock_main
#     test_helper
#     dlt_mcu
# )

# add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})
