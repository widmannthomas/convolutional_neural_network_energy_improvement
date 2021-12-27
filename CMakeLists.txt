cmake_minimum_required(VERSION 3.12)

include(pico-tflmicro/pico_sdk_import.cmake)

project(pico-tflmicro-cnn-energy C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

pico_sdk_init()

add_subdirectory(pico-tflmicro)
add_subdirectory("src/base/log")
add_subdirectory("src/base/dataprovider")
add_subdirectory("src/base/json")
add_subdirectory("src/base/statemachine")
add_subdirectory("src/base/communication")
add_subdirectory("src/hello_world")
add_subdirectory("src/mnist")
add_subdirectory("src/timing")
add_subdirectory("src/test_dataprovider")
add_subdirectory("src/test_communication")