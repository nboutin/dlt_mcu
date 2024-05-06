cmake_minimum_required(VERSION 3.28)
project(dlt_mcu_ut)

# # subhook requires to link with static libs, so set BUILD_SHARED_LIBS OFF
# set(BUILD_SHARED_LIBS OFF)
# # Adding Cutie framework
# get_filename_component(CUTIE_DIR ${TOP_DIR}/other-tools/cutie_framework/cutie REALPATH)
# get_filename_component(DLFCN_DIR ${TOP_DIR}/other-tools/cutie_framework/dlfcn-win32 REALPATH)
# include(${CUTIE_DIR}/cutie.cmake)

# include(CTest)
# enable_testing()

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

add_cutie_test_target(
  NAME ${PROJECT_NAME}
  TEST suites/it_dlt_client.cpp
  SOURCES $<TARGET_OBJECTS:buffer_mcu> $<TARGET_OBJECTS:ring_buffer_mcu>
  LINK_LIBRARIES dlt_mcu test_helper
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
