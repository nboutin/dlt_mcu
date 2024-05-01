cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(dlt_mcu)

set(target_name dlt_mcu)

add_library(${target_name} OBJECT
  source/dlt_client.c
  source/dlt_context.c
  source/dlt_frame.c
  source/dlt_server.c
  source/datalink/dlt_datalink_serial.c
  source/datalink/dlt_datalink.c
  conf/dlt_conf.c
  conf/dlt_uart.c
)

target_include_directories(${target_name}
  PUBLIC
    include
  PRIVATE
    source
    source/datalink
    conf
)

target_compile_definitions(${target_name}
  PUBLIC
    # DLT_WITH_FLOAT
  PRIVATE
    DLT_WITH_ECU_ID
    DLT_WITH_SERIAL
  # --- Tests
    # $<$<NOT:$<BOOL:${BUILD_TESTS}>>:STATIC=static>
    # $<$<BOOL:${BUILD_TESTS}>:STATIC=>
)

include(cmake/get_cpm.cmake)
include(cmake/CPM.cmake)

CPMAddPackage("gh:nboutin/buffer_mcu@0.2.0")
CPMAddPackage("gh:nboutin/ring_buffer_mcu@0.1.0")

target_link_libraries(${target_name}
  PUBLIC
    buffer_mcu
    ring_buffer_mcu
  PRIVATE
)

# ---

# add_subdirectory(test)
