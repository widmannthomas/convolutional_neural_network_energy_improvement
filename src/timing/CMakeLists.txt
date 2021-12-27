
cmake_minimum_required(VERSION 3.12)

project(mnist C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(timing "")

target_include_directories(timing
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
    timing
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(timing
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  timing
  pico-tflmicro
  hardware_pwm
)

pico_add_extra_outputs(timing)
pico_enable_stdio_usb(timing 1)
pico_enable_stdio_uart(timing 0)
