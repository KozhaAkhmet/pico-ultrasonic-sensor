add_executable(filter_test filter_test.cpp)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(filter_test 
pico_stdlib
hardware_uart 
pico_ultrasonic
)

pico_enable_stdio_usb(filter_test 1)
pico_enable_stdio_uart(filter_test 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(filter_test)

# add url via pico_set_program_url
example_auto_set_url(filter_test)
