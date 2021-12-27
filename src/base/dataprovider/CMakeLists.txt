
cmake_minimum_required(VERSION 3.12)

project(dataprovider C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_library(libdataprovider "")

target_include_directories(libdataprovider
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  libdataprovider
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(libdataprovider
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/dataproviderserial.cpp
  ${CMAKE_CURRENT_LIST_DIR}/dataproviderserial.h
  ${CMAKE_CURRENT_LIST_DIR}/idataprovider.h
  ${CMAKE_CURRENT_LIST_DIR}/dataconverter.h
)

target_link_libraries(
  libdataprovider
  pico-tflmicro
  hardware_pwm
)
