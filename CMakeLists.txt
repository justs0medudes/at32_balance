#[=[
CMake configuration for AT32F403A_407 Balance v0.1 project
# By justsomedudes
# 28 January 2026
]=]

cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME at32_balance_v0_1)
# Include toolchain file
include(${CMAKE_SOURCE_DIR}/gcc-arm-none-eabi.cmake)

project(${PROJECT_NAME} LANGUAGES C ASM)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# Add executable
add_executable(${PROJECT_NAME})

# Target sources
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/sys_clock.c
    ${CMAKE_SOURCE_DIR}/src/sys_delay.c
    ${CMAKE_SOURCE_DIR}/src/sys_dma.c
    ${CMAKE_SOURCE_DIR}/src/sys_gpio.c
    ${CMAKE_SOURCE_DIR}/src/sys_isr.c
    ${CMAKE_SOURCE_DIR}/src/sys_spi.c
    ${CMAKE_SOURCE_DIR}/src/sys_tick.c
    ${CMAKE_SOURCE_DIR}/src/sys_tmr.c
    ${CMAKE_SOURCE_DIR}/src/sys_usart.c
    ${CMAKE_SOURCE_DIR}/src/periph_led.c
    ${CMAKE_SOURCE_DIR}/src/periph_mpu.c
    ${CMAKE_SOURCE_DIR}/src/periph_encoder.c

    # toolchain support files
    ${CMAKE_SOURCE_DIR}/syscalls.c

    # vendor core file
    ${CMAKE_SOURCE_DIR}/libraries/cmsis/cm4/device_support/system_at32f403a_407.c

    # Startup (adjust filename!)
    ${CMAKE_SOURCE_DIR}/startup_at32f403a_407.s

    #[[
    IMPORTANT: Add every vendor library used in here!!!
    ]]
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_acc.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_adc.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_bpr.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_can.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_crc.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_crm.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_dac.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_debug.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_dma.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_emac.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_exint.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_flash.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_gpio.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_i2c.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_misc.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_pwc.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_rtc.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_sdio.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_spi.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_tmr.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_usart.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_usb.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_wdt.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_wwdt.c
    ${CMAKE_SOURCE_DIR}/libraries/drivers/src/at32f403a_407_xmc.c
)

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/libraries/drivers/inc
    ${CMAKE_SOURCE_DIR}/libraries/cmsis/cm4/core_support
    ${CMAKE_SOURCE_DIR}/libraries/cmsis/cm4/device_support
)

# Set macros
target_compile_definitions(${PROJECT_NAME} PRIVATE
    USE_STDPERIPH_DRIVER
    AT32F403AVGT7
    $<$<CONFIG:Debug>:DEBUG>
)

# Compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m4
  -mthumb
  -ffunction-sections
  -fdata-sections
  -Wall
  -Wextra
)


# Add a custom button for OpenOCD debugging on CLion
add_custom_target(openocd_flash
    COMMAND openocd
        -d2
        -l openocd.log
        -s ~/tool-openocd-at32/scripts
        -f interface/atlink.cfg
        -f target/at32f403axG.cfg
        -c "program $<TARGET_FILE:${PROJECT_NAME}> verify reset exit"
    USES_TERMINAL
)