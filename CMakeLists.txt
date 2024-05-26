cmake_minimum_required(VERSION 3.28)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/get_cpm.cmake)
include(cmake/CPM.cmake)
if(DLT_MCU_TEST)
  include(cmake/cutie_config.cmake)
endif()

# ---

project(dlt_mcu)

CPMAddPackage("gh:nboutin/buffer_mcu@1.0.0")
CPMAddPackage("gh:nboutin/ring_buffer_mcu@1.0.0")

add_library(${PROJECT_NAME} OBJECT
  source/dlt_client.c
  source/dlt_context.c
  source/dlt_frame.c
  source/dlt_server.c
  source/datalink/dlt_datalink_serial.c
  source/datalink/dlt_datalink.c
  conf/dlt_conf.c
  conf/dlt_uart.c
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
    conf
  PRIVATE
    source
    source/datalink
    conf
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    # DLT_WITH_FLOAT
  PRIVATE
    DLT_WITH_ECU_ID
    DLT_WITH_SERIAL
  # --- Tests
    # $<$<NOT:$<BOOL:${BUILD_TESTS}>>:STATIC=static>
    # $<$<BOOL:${BUILD_TESTS}>:STATIC=>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    buffer_mcu
    ring_buffer_mcu
  PRIVATE
)

# ---

if(DLT_MCU_TEST)
  add_subdirectory(test)
endif()
