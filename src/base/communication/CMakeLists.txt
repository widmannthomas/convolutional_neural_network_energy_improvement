
cmake_minimum_required(VERSION 3.12)

project(communication C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_library(libcommunication "")

target_include_directories(libcommunication
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
    libcommunication
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(libcommunication
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/uart_helper.cpp
  ${CMAKE_CURRENT_LIST_DIR}/communicationhandler.cpp
  ${CMAKE_CURRENT_LIST_DIR}/communicationhandler.h
  ${CMAKE_CURRENT_LIST_DIR}/command.h
  ${CMAKE_CURRENT_LIST_DIR}/uart_helper.h
)

target_link_libraries(
  libcommunication
  pico-tflmicro
  hardware_pwm
)
