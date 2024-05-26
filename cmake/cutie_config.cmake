project(${PROJECT_NAME}_test LANGUAGES CXX C)

set(BUILD_SHARED_LIBS OFF)
set(DLFCN_BUILD_TESTS OFF)
set(CUTIE_GTEST_XML ON)

CPMAddPackage(
  NAME cutie
  GITHUB_REPOSITORY nboutin/Cutie
  VERSION 1.4.0
)

get_filename_component(CUTIE_DIR ${cutie_SOURCE_DIR} REALPATH)
include(${CUTIE_DIR}/cutie.cmake)

# FIXME Need this otherwise there is link error...
add_cutie_test_target(NAME "samples_ut" SOURCES ${CUTIE_DIR}/samples/sample_code.cpp)
