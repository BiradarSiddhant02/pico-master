cmake_minimum_required(VERSION 3.21)

include(src/pico_sdk_import.cmake)

project(pico-signal-master)

pico_sdk_init()

add_executable(signal-master
    src/main.c
    src/master.c
    src/master.h
)



target_include_directories(signal-master PRIVATE src)  # Include src/ directory for header files

target_link_libraries(signal-master pico_stdlib hardware_spi)

pico_enable_stdio_usb(signal-master 1)
pico_enable_stdio_uart(signal-master 0)

pico_add_extra_outputs(signal-master)
