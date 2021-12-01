# Build configs
set(IS_STM32 ON)
set(DEBUG OFF)
set(SANITIZER OFF) # Options: OFF, address, leak, thread, undefined, memory

if (${IS_STM32})
    add_compile_definitions(IS_STM32)
endif ()

if (${DEBUG})
    add_compile_definitions(DEBUG)
endif ()

