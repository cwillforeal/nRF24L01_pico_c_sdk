cmake_minimum_required(VERSION 3.13)

# Configure the examples 
add_executable(tx_example
    main.c
)

pico_enable_stdio_usb(tx_example 1)
pico_enable_stdio_uart(tx_example 1)
pico_add_extra_outputs(tx_example)

target_link_libraries(tx_example
    pico_stdlib
    nrf24l01
    hardware_spi
)
