cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(sample C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++ CACHE PATH "" FORCE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# Uncomment if your target board is PICO W
set(PICO_BOARD pico_w)

pico_sdk_init()

# Create the high level library
add_library(nrf24l01 
    nrf24l01.c
    nrf24l01_low_level.c
)

target_link_libraries(nrf24l01
    pico_stdlib
    hardware_spi
)
target_include_directories(nrf24l01 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add in the subdirectories
add_subdirectory(examples)
