
cmake_minimum_required(VERSION 3.12)

project(log C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_library(liblog "")

target_include_directories(liblog
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
    liblog
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(liblog
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/log.h
)

target_link_libraries(
  liblog
  pico-tflmicro
  hardware_pwm
)
