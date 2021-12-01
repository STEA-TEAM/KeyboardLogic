# Build configs
set(DEBUG ON)
set(SANITIZER leak) # Options: OFF, address, leak, thread, undefined, memory

if (${IS_STM32})
    add_compile_definitions(IS_STM32)
endif ()

if (${DEBUG})
    add_compile_definitions(DEBUG)
endif ()

