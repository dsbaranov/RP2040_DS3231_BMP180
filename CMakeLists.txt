# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(RP2040_IIC_DS3231_BMP_180 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

set(LIBDIR ${CMAKE_CURRENT_LIST_DIR}/lib)

set(LIBRARIES
${LIBDIR}/bmp180/bmp180.h
${LIBDIR}/bmp180/bmp180.cpp
${LIBDIR}/bmp180/bmp180_domain.h
${LIBDIR}/bmp180/bmp180_domain.cpp
${LIBDIR}/bmp180/bmp180_common.h
${LIBDIR}/bmp180/bmp180_registers.h

${LIBDIR}/ds3231/ds3231.h
${LIBDIR}/ds3231/ds3231.cpp
${LIBDIR}/ds3231/ds3231_common.h
${LIBDIR}/ds3231/ds3231_common.cpp
${LIBDIR}/ds3231/ds3231_domain.h
${LIBDIR}/ds3231/ds3231_domain.cpp
${LIBDIR}/ds3231/ds3231_registers.h

${LIBDIR}/i2c/i2c_entity.h
${LIBDIR}/i2c/i2c_entity.cpp

${LIBDIR}/i2c/i2c_device.h
${LIBDIR}/i2c/i2c_device.cpp

${LIBDIR}/ssd1315/ssd1315.h
${LIBDIR}/ssd1315/ssd1315.cpp
${LIBDIR}/ssd1315/ssd1315_common.h
${LIBDIR}/ssd1315/ssd1315_common.cpp
${LIBDIR}/ssd1315/ssd1315_domain.h
${LIBDIR}/ssd1315/ssd1315_domain.cpp
${LIBDIR}/ssd1315/ssd1315_registers.h
${LIBDIR}/ssd1315/ssd1306_font.h
${LIBDIR}/ssd1315/ssd1315_example.h
${LIBDIR}/ssd1315/ssd1315_example.cpp
${LIBDIR}/ssd1315/ssd1315_font.h
)

# Add executable. Default name is the project name, version 0.1

add_executable(RP2040_IIC_DS3231_BMP_180 RP2040_IIC_DS3231_BMP_180.cpp ${LIBRARIES})

target_include_directories(RP2040_IIC_DS3231_BMP_180 PRIVATE ${LIBDIR})

pico_set_program_name(RP2040_IIC_DS3231_BMP_180 "RP2040_IIC_DS3231_BMP_180")
pico_set_program_version(RP2040_IIC_DS3231_BMP_180 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(RP2040_IIC_DS3231_BMP_180 0)
pico_enable_stdio_usb(RP2040_IIC_DS3231_BMP_180 1)

# Add the standard library to the build
target_link_libraries(RP2040_IIC_DS3231_BMP_180
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(RP2040_IIC_DS3231_BMP_180 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(RP2040_IIC_DS3231_BMP_180 
        hardware_i2c
        )

pico_add_extra_outputs(RP2040_IIC_DS3231_BMP_180)

