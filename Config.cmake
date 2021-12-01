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

# RGB led configs
set(ENABLE_WS2812_DRIVER ON)
set(ENABLE_KEY_LED ON)
set(LED_STRIP_COUNT 1)

if(${ENABLE_WS2812_DRIVER})
    add_compile_definitions(WS2812_RGB)
    add_compile_definitions(WS2812_STRIP_NUM=${LED_STRIP_COUNT})
    if(${ENABLE_KEY_LED})
        add_compile_definitions(KEY_WS2812_RGB)
    endif()
endif()

