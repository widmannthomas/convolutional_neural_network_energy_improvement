
cmake_minimum_required(VERSION 3.12)

project(test_communication C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_communication "")

target_include_directories(test_communication
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  test_communication
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(test_communication
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  test_communication
  libcommunication
  pico-tflmicro
  hardware_pwm
)

pico_add_extra_outputs(test_communication)
pico_enable_stdio_usb(test_communication 1)
pico_enable_stdio_uart(test_communication 0)
