cmake_minimum_required(VERSION 3.13)

# Configure the examples 
add_executable(rx_example
    main.c
)

pico_enable_stdio_usb(rx_example 1)
pico_enable_stdio_uart(rx_example 1)
pico_add_extra_outputs(rx_example)

target_link_libraries(rx_example
    pico_stdlib
    nrf24l01
    hardware_spi
)
