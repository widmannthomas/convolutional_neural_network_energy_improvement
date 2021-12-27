
cmake_minimum_required(VERSION 3.12)

project(mnist C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

if(FALSE)
add_executable(mnist_test "")

target_include_directories(mnist_test
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  mnist_test
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(mnist_test
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/mnist_test.cpp
  ${CMAKE_CURRENT_LIST_DIR}/model.cpp
  ${CMAKE_CURRENT_LIST_DIR}/model.h
)

target_link_libraries(
  mnist_test
  pico-tflmicro
  hardware_pwm
  pico-tflmicro_test
)

pico_add_extra_outputs(mnist_test)
endif()


add_executable(mnist "")

target_include_directories(mnist
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  mnist
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(mnist
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/core.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ml/MLCore.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ResultReporter.cpp
  ${CMAKE_CURRENT_LIST_DIR}/test_data/dataprovidertest.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.h
  ${CMAKE_CURRENT_LIST_DIR}/core.h
  ${CMAKE_CURRENT_LIST_DIR}/train/model.h
  ${CMAKE_CURRENT_LIST_DIR}/ml/MLCore.h
  ${CMAKE_CURRENT_LIST_DIR}/ResultReporter.h
)

target_link_libraries(
  mnist
  libdataprovider
  libcommunication
  libjson
  libstatemachine
  pico-tflmicro
  hardware_pwm
)

pico_add_extra_outputs(mnist)
pico_enable_stdio_usb(mnist 1)
pico_enable_stdio_uart(mnist 0)
