
cmake_minimum_required(VERSION 3.12)

include(../../../pico-tflmicro/pico_sdk_import.cmake)

project(statemachine C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_library(libstatemachine "")

target_include_directories(libstatemachine
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  libstatemachine
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(libstatemachine
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/finitestatemachine.h
)

target_link_libraries(
  libstatemachine
  pico_stdlib
)
