#此文件从模板自动生成! 请勿更改!
cmake_minimum_required(VERSION 3.20)
# Project configurations
include(Config.cmake)
# Key code definitions
include(KeyDef.cmake)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

if (${IS_STM32})
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_VERSION 1)
    # specify cross compilers and tools
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
    set(CMAKE_AR arm-none-eabi-ar)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    set(CMAKE_OBJDUMP arm-none-eabi-objdump)
    set(SIZE arm-none-eabi-size)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
    # project settings
    project(MatrixKeyboard C CXX ASM)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_C_STANDARD 11)
    #Uncomment for hardware floating point
    #add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
    #add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
    #add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

    #Uncomment for software floating point
    #add_compile_options(-mfloat-abi=soft)

    add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
    add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

    # uncomment to mitigate c++17 absolute addresses warnings
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

    include_directories(USB_DEVICE/App USB_DEVICE/Target Core/Inc Drivers/STM32F1xx_HAL_Driver/Inc Drivers/STM32F1xx_HAL_Driver/Inc/Legacy Middlewares/ST/STM32_USB_Device_Library/Core/Inc Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc Drivers/CMSIS/Device/ST/STM32F1xx/Include Drivers/CMSIS/Include)

    add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xB)

    file(GLOB_RECURSE SOURCES "Core/*.*" "Middlewares/*.*" "Drivers/*.*" "USB_DEVICE/*.*")

    set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld)

    add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
    add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
    add_link_options(-T ${LINKER_SCRIPT})

    add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/custom_driver/Src CDRV_SRC)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/keyboard_logic/Src KBDL_SRC)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/universal_func/Src UNIFC_SRC)

    target_include_directories(${PROJECT_NAME}.elf PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/custom_driver/Inc
            ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_logic/Inc
            ${CMAKE_CURRENT_SOURCE_DIR}/universal_func/Inc)

    target_sources(${PROJECT_NAME}.elf PRIVATE
            ${CDRV_SRC}
            ${KBDL_SRC}
            ${UNIFC_SRC})

    set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
            COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
            COMMENT "Building ${HEX_FILE}
    Building ${BIN_FILE}")
else ()
    # project settings
    project(MatrixKeyboard C CXX)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_C_STANDARD 11)

    if (NOT ${SANITIZER} STREQUAL "OFF")
        message(STATUS "Use Google Sanitizer: ${SANITIZER}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=${SANITIZER} -g")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${SANITIZER} -g")
    endif ()

    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/keyboard_logic/Src KBDL_SRC)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/universal_func/Src UNIFC_SRC)

    add_executable(${PROJECT_NAME} main.c)

    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_logic/Inc
            ${CMAKE_CURRENT_SOURCE_DIR}/universal_func/Inc)

    target_sources(${PROJECT_NAME} PRIVATE
            ${KBDL_SRC}
            ${UNIFC_SRC})
endif ()